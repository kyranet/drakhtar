// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitsController.h"

#include "Errors/DrakhtarError.h"
#include "EventListeners/EventListener.h"
#include "GameObjects/Battalion.h"
#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "GameObjects/HealthBar.h"
#include "GameObjects/Text.h"
#include "GameObjects/Unit.h"
#include "Managers/GameManager.h"
#include "Managers/State.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Structures/Game.h"
#include "Structures/SceneMachine.h"
#include "Structures/Team.h"
#include "Structures/Texture.h"
#include "Structures/Tween.h"

UnitsController::UnitsController(Board* board, GameScene* scene, Team* team,
                                 Team* oppositeTeam)
    : board_(board), scene_(scene), team_(team), oppositeTeam_(oppositeTeam) {}

UnitsController::~UnitsController() = default;

void UnitsController::start() {
  getState()->setController(this);

  // Reset this controller's state
  hasAttacked_ = false;
  hasMoved_ = false;

  // Deactivate all listeners
  for (auto& listener : listeners_) listener->setActive(true);
  activeUnit_ = getState()->getActiveUnit();
}

void UnitsController::finish() {
  if (activeUnit_ != nullptr) {
    for (auto& listener : listeners_) listener->setActive(false);
    activeUnit_ = nullptr;
  }

  // Update the turn bar
  const auto state = getState();
  state->next();

  if (state->getActiveUnit()->getTeam() == team_) {
    getBoard()->getScene()->processNextTick([this]() { start(); });
  } else {
    // Once this controller is finished, start the controller of the opposite
    // team.
    getBoard()->getScene()->processNextTick(
        [this]() { oppositeTeam_->getController()->start(); });
  }
}

Board* UnitsController::getBoard() const { return board_; }
Unit* UnitsController::getActiveUnit() const { return activeUnit_; }
State* UnitsController::getState() const {
  return reinterpret_cast<GameScene*>(getBoard()->getScene())->getState();
}
bool UnitsController::hasAttacked() const { return hasAttacked_; }
bool UnitsController::hasMoved() const { return hasMoved_; }

void UnitsController::onDamage(const UnitState& stats) {
  stats.unit_->getHealthBar()->takeDamage(stats.health_);
  stats.unit_->getHealthText()->setText(stats.unit_->healthToString());
  stats.unit_->getHealthText()->setColor({255, 255, 255, 0});

  if (!stats.unit_->isCommander()) {
    reinterpret_cast<Battalion*>(stats.unit_)
        ->setBattalionSize(stats.battalionSize_);
  }
}

void UnitsController::onKill(const UnitState& stats) {
  onDamage(stats);

  // Add the money
  if (stats.team_ == Color::RED) {
    GameManager::getInstance()->addMoney(stats.prize_);
  }

  stats.unit_->getTexture()->setAnimationOnce("death");
  stats.unit_->getTexture()->setAnimationOnEnd([this, stats]() {
    // Don't make it renderable after dying.
    stats.unit_->setRenderable(false);

    // If the unit who got killed is the commander, it should finish the scene
    if (stats.unit_->isCommander()) {
      reinterpret_cast<GameScene*>(Game::getSceneMachine()->getCurrentScene())
          ->gameOver(stats.team_ != Color::BLUE);
      return;
    } else {
      reinterpret_cast<Battalion*>(stats.unit_)
          ->setBattalionSize(stats.battalionSize_);
    }

    // This is in the case the unit dies on counter-attack, skip turn
    if (stats.unit_ == activeUnit_) {
      // Clean up to signal the controller to finish the turn
      activeUnit_ = nullptr;

      // Unit dies to counter-attack
      finish();
    }

    // Clean up
    stats.unit_->kill();
  });
}

std::vector<Vector2D<double>> UnitsController::pathToRoute(
    const std::vector<Vector2D<uint16_t>>& path) const {
  std::vector<Vector2D<double>> vector;
  vector.reserve(path.size());

  const auto board = getBoard();
  for (const auto& element : path) {
    const auto box = board->getBoxAt(element.getX(), element.getY());
    const auto pos = box->getPosition();
    const auto size = box->getSize();
    vector.emplace_back(pos.getX() + size.getX() / 2.0,
                        pos.getY() + size.getY() / 2.0);
  }
  return vector;
}

void UnitsController::setTutorialDone(bool done) { tutorialDone_ = done; }

void UnitsController::move(Vector2D<uint16_t> from, Vector2D<uint16_t> to) {
  const auto unit = activeUnit_;

  const auto state = getState();
  const auto path = state->findPath(from, to);
  const auto stats = state->getAt(from);
  const auto box = getBoard()->getBoxAt(to.getX(), to.getY());
  unit->moveToBox(box);
  state->move(from, to);

  scene_->getTweenManager()
      ->create()
      ->setRoute(pathToRoute(path))
      ->setDuration(static_cast<int>(
          floor(static_cast<double>(path.size()) * GAME_FRAMERATE * 0.25)))
      ->setOnStart([unit]() { unit->getTexture()->setAnimation("walk"); })
      ->setOnUpdate([unit](Vector2D<double> updated) {
        unit->setPosition({static_cast<int>(std::floor(updated.getX())),
                           static_cast<int>(std::floor(updated.getY()))});
      })
      ->setOnComplete([this, unit]() {
        unit->getTexture()->setAnimation("default");
        hasMoved_ = true;
        canMove_ = false;

        onComplete();
      });
}

void UnitsController::onComplete() {}

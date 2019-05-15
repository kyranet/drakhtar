// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitsController.h"
#include "Errors/DrakhtarError.h"
#include "EventListeners/EventListener.h"
#include "GameObjects/Board.h"
#include "GameObjects/HealthBar.h"
#include "GameObjects/Text.h"
#include "GameObjects/Unit.h"
#include "Managers/GameManager.h"
#include "Managers/State.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"

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
  activeUnit_->onSelect();
}

void UnitsController::finish() {
  if (activeUnit_ != nullptr) {
    activeUnit_->onDeselect();
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
}

void UnitsController::onKill(const UnitState& stats) {
  if (stats.unit_ == activeUnit_) {
    // Clean up to signal the controller to finish the turn
    activeUnit_ = nullptr;

    // Unit dies to counter-attack
    finish();
  }

  stats.unit_->kill();
  if (stats.unit_->getTeam()->getColor() == Color::RED) {
    GameManager::getInstance()->addMoney(stats.prize_);
  }
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "PlayerController.h"
#include <iostream>
#include "Controllers/Handlers/PlayerHandler.h"
#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "GameObjects/Button.h"
#include "GameObjects/Commanders/Commander.h"
#include "GameObjects/TurnBar.h"
#include "GameObjects/Unit.h"
#include "Managers/GameManager.h"
#include "Managers/Input.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/State.h"
#include "Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Structures/Team.h"
#include "Structures/Texture.h"
#include "Structures/Tween.h"
#include "Utils/Constants.h"

PlayerController::PlayerController(Board* board, GameScene* scene, Team* team,
                                   Team* oppositeTeam)
    : UnitsController(board, scene, team, oppositeTeam) {
  const auto handler = new PlayerHandler(this);
  handler->setActive(false);
  listeners_.push_back(handler);
  board->addEventListener(handler);
}

void PlayerController::onClickMove(Box* boxClicked) {
  if (locked_ || !tutorialDone_) return;
  // Checks if the box clicked is within movement range
  const auto state = getState();

  if (!state->isInMoveRange(activeUnit_->getBox()->getIndex(),
                            boxClicked->getIndex(),
                            activeUnit_->getStats().moveRange)) {
    SDLAudioManager::getInstance()->playChannel(3, 0, 0);
    return;
  }

  const auto path = state->findPath(activeUnit_->getBox()->getIndex(),
                                    boxClicked->getIndex());

  locked_ = true;
  SDLAudioManager::getInstance()->playChannel(0, 0, 0);
  const auto unit = activeUnit_;
  unit->moveToBox(boxClicked);

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
      ->setOnComplete([this, unit, boxClicked, state]() {
        unit->getTexture()->setAnimation("default");
        hasMoved_ = true;
        locked_ = false;

        const auto stats = state->getAt(unit->getBoxPosition());
        // If there are enemies in range, highlight them, otherwise skip turn
        if (!hasAttacked_ &&
            state->isInRange(boxClicked->getIndex(), stats.position_,
                             stats.attackRange_)) {
          highlightCells();
          SDLAudioManager::getInstance()->setChannelVolume(30, 0);
          SDLAudioManager::getInstance()->playChannel(4, 0, 0);
        } else {
          hasAttacked_ = true;
          if (!canCastSkills()) finish();
        }
      });
}

void PlayerController::onClickAttack(Box* boxClicked) {
  auto unit = boxClicked->getContent();
  if (tutorialDone_) {
    // If the box clicked was empty, skip
    if (!unit) return;

    // If the unit is from the same team, skip
    if (unit->getTeam() == team_) return;

    const auto state = getState();
    const auto stats = state->getAt(unit->getBoxPosition());

    // If the selected unit is not in the attack range, skip
    if (!state->isInRange(unit->getBoxPosition(), boxClicked->getIndex(),
                          stats.attackRange_))
      return;

    hasAttacked_ = true;

    activeUnit_->getTexture()->setAnimationOnce("attack");
    activeUnit_->attack(unit, true);
    SDLAudioManager::getInstance()->playChannel(5, 0, 0);

    const auto unitStats = unit->getStats();

    // Enemy dies
    if (unit->getHealth() <= 0) {
      // Unit dies to attack
      if (unit->getTeam()->getColor() == Color::RED) {
        GameManager::getInstance()->addMoney(unitStats.prize);
      }
      boxClicked->destroyContent();
    } else if (activeUnit_->getHealth() <= 0) {
      // Unit dies to counter-attack
      unit->getBox()->destroyContent();
      finish();
      return;
    }

    if (hasMoved_) {
      // If no actions left, reset and skip turn
      if (!canCastSkills()) finish();
    } else {
      // Re-highlight board
      highlightCells();
    }
  }
}

void PlayerController::start() {
  UnitsController::start();
  if (!activeUnit_) return UnitsController::finish();

  skipTurnButton_ =
      new Button(scene_, TextureManager::get("Button-SkipTurn"),
                 Vector2D<int>(WIN_WIDTH / 13, WIN_HEIGHT - WIN_HEIGHT / 8),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 10.5),
                               static_cast<int>(WIN_HEIGHT / 6.75)),
                 [this]() { finish(); }, " ", "ButtonFont");
  scene_->addGameObject(skipTurnButton_);
  highlightCells();
}

void PlayerController::finish() {
  // board_->resetCellsToBase();
  scene_->removeGameObject(skipTurnButton_);
  UnitsController::finish();
}

bool PlayerController::getLocked() const { return locked_; }

void PlayerController::setTutorialDone(bool done) { tutorialDone_ = done; }

bool PlayerController::gettutorialDone() { return tutorialDone_; }

bool PlayerController::canCastSkills() {
  if (tutorialDone_) {
    Commander* commander = dynamic_cast<Commander*>(activeUnit_);
    if (commander != nullptr) {
      for (auto skill : commander->getSkills()) {
        if (skill->getRemainingCooldown() == 0) {
          highlightCells();
          return true;
        }
      }
    }
  }
  return false;
}

void PlayerController::highlightCells() {
  // TODO(kyranet): Fix this
  // Reset board
  // board_->resetCellsToBase();

  // Highlight active unit
  activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);

  // Highlight movable cells
  // if (!hasMoved_)
  //   board_->highlightCellsInRange(activeUnit_->getBox(),
  //                                 activeUnit_->getStats().moveRange);

  // Highlight attackable cells
  // if (!hasAttacked_)
  //   board_->highlightEnemiesInRange(activeUnit_->getBox(),
  //                                   activeUnit_->getStats().attackRange);
}

std::vector<Vector2D<double>> PlayerController::pathToRoute(
    const std::vector<Vector2D<byte>>& path) const {
  std::vector<Vector2D<double>> vector;
  vector.reserve(path.size());

  // TODO(kyranet): Add hooks to Box. Maybe store Box instead of Unit in
  //  StateUnit?
  // for (const auto& element : path) {
  //   const auto box = getBoxAt(element.getX(), element.getY());
  //   const auto pos = box->getPosition();
  //   const auto size = box->getSize();
  //   vector.emplace_back(pos.getX() + size.getX() / 2.0,
  //                       pos.getY() + size.getY() / 2.0);
  // }
  return vector;
}

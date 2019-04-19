// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "PlayerController.h"

#include <iostream>

#include "Controllers/Handlers/PlayerHandler.h"
#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "GameObjects/TurnBar.h"
#include "GameObjects/Unit.h"
#include "Managers/GameManager.h"
#include "Managers/Input.h"
#include "Managers/SDLAudioManager.h"
#include "Scenes/GameScene.h"
#include "Structures/Team.h"
#include "Structures/Texture.h"
#include "Structures/Tween.h"
#include "Utils/Constants.h"

PlayerController::PlayerController(Board* board, TurnBar* turnBar,
                                   GameScene* scene, Team* team,
                                   Team* oppositeTeam)
    : UnitsController(board, turnBar, scene, team, oppositeTeam) {
  const auto handler = new PlayerHandler(this);
  handler->setActive(false);
  listeners_.push_back(handler);
  board->addEventListener(handler);
}

void PlayerController::onClickMove(Box* boxClicked) {
  // Checks if the box clicked is within movement range
  if (!locked_ && board_->isInMoveRange(activeUnit_->getBox(), boxClicked,
                                        activeUnit_->getStats().moveRange)) {
    const auto path = board_->findPath(activeUnit_->getBox()->getIndex(),
                                       boxClicked->getIndex());

    locked_ = true;
    SDLAudioManager::getInstance()->playChannel(0, 0, 0);
    const auto unit = activeUnit_;
    scene_->getTweenManager()
        ->create()
        ->setRoute(board_->pathToRoute(path))
        ->setDuration(static_cast<int>(
            floor(static_cast<double>(path.size()) * GAME_FRAMERATE * 0.25)))
        ->setOnUpdate([unit](Vector2D<double> updated) {
          unit->setPosition({static_cast<int>(std::floor(updated.getX())),
                             static_cast<int>(std::floor(updated.getY()))});
        })
        ->setOnComplete([this, unit, boxClicked]() {
          unit->moveToBox(boxClicked);
          hasMoved_ = true;
          locked_ = false;
          // If there are enemies in range, highlight them, otherwise skip turn
          if (board_->isEnemyInRange(boxClicked,
                                     unit->getStats().attackRange)) {
            board_->resetCellsToBase();
            unit->getBox()->setCurrentTexture(TextureInd::ACTIVE);
            board_->highlightEnemiesInRange(unit->getBox(),
                                            unit->getStats().attackRange);
            SDLAudioManager::getInstance()->setChannelVolume(30, 0);
            SDLAudioManager::getInstance()->playChannel(4, 0, 0);
          } else {
            finish();
          }

          // If no actions left, reset and skip turn
          if (hasAttacked_) {
            finish();
          }
        });
  } else {
    std::cout << "Out of movement range!\n";
    SDLAudioManager::getInstance()->playChannel(3, 0, 0);
  }
}

void PlayerController::onClickAttack(Box* boxClicked) {
  Unit* enemyUnit = boxClicked->getContent();
  if (enemyUnit != nullptr) {
    // Unit clicked if from a different team and in range
    if (enemyUnit->getTeam() != activeUnit_->getTeam() &&
        board_->isInRange(activeUnit_->getBox(), boxClicked,
                          activeUnit_->getStats().attackRange)) {
      activeUnit_->getTexture()->setAnimationOnce("attack");
      activeUnit_->attack(enemyUnit, false);
      SDLAudioManager::getInstance()->playChannel(5, 0, 0);

      hasAttacked_ = true;

      // Enemy dies
      if (enemyUnit->getStats().health <= 0) {
        // Unit dies to attack
        if (enemyUnit->getTeam()->getColor() == Color::RED) {
          GameManager::getInstance()->addMoney(enemyUnit->getStats().prize);
        }
        boxClicked->destroyContent();
      } else if (activeUnit_->getStats().health <= 0) {
        // Unit dies to counter-attack
        activeUnit_->getBox()->destroyContent();
        finish();
        return;
      }

      if (hasMoved_) {
        // If no actions left, reset and skip turn
        finish();
      } else {
        // Re-highlight board
        board_->resetCellsToBase();
        activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
        board_->highlightCellsInRange(activeUnit_->getBox(),
                                      activeUnit_->getStats().moveRange);
      }
    }
  }
}

void PlayerController::start() {
  UnitsController::start();

  activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
  board_->highlightCellsInRange(activeUnit_->getBox(),
                                activeUnit_->getStats().moveRange);
  board_->highlightEnemiesInRange(activeUnit_->getBox(),
                                  activeUnit_->getStats().attackRange);
}

void PlayerController::finish() {
  board_->resetCellsToBase();
  UnitsController::finish();
}

bool PlayerController::getLocked() const { return locked_; }

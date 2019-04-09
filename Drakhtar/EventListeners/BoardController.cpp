// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "BoardController.h"
#include <iostream>
#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "GameObjects/TurnBar.h"
#include "GameObjects/Unit.h"
#include "Managers/GameManager.h"
#include "Managers/SDLAudioManager.h"
#include "Scenes/GameScene.h"
#include "Structures/Team.h"
#include "Structures/Texture.h"
#include "Structures/Tween.h"
#include "Utils/Constants.h"

BoardController::BoardController(Board *board, TurnBar *turnBar,
                                 GameScene *scene)
    : board_(board), turnBar_(turnBar), scene_(scene), ListenerOnClick(board) {
  activeUnit_ = turnBar_->getFrontUnit();
  activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
  board_->highlightCellsInRange(activeUnit_->getBox(),
                                activeUnit_->getStats().moveRange);
  board_->highlightEnemiesInRange(activeUnit_->getBox(),
                                  activeUnit_->getStats().attackRange);
}

void BoardController::run(const SDL_Event event) {
  // Captures mouse event
  ListenerOnClick::run(event);

  // If no actions left, reset and skip turn
  if (hasMoved_ && hasAttacked_) {
    advanceTurn();
  }
}

void BoardController::onClickStop(const SDL_Point point) {
  const auto boxClicked = board_->getBoxAtCoordinates(point);

  if (boxClicked != nullptr) {
    if (boxClicked->isEmpty() && !hasMoved_) {
      onClickMove(boxClicked);
    } else if (!hasAttacked_) {
      onClickAttack(boxClicked);
    }
  }
}

void BoardController::onClickMove(Box *boxClicked) {
  // If this BoardController is stopped, don't run
  if (isTweening_) return;

  // Checks if the box clicked is within movement range
  if (board_->isInMoveRange(activeUnit_->getBox(), boxClicked,
                            activeUnit_->getStats().moveRange)) {
    const auto path = board_->findPath(activeUnit_->getBox()->getIndex(),
                                       boxClicked->getIndex());

    isTweening_ = true;
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
          isTweening_ = false;
          // If there are enemies in range, highlight them, otherwise skip turn
          if (board_->isEnemyInRange(boxClicked, unit->getStats().attackRange)) {
            board_->resetCellsToBase();
            unit->getBox()->setCurrentTexture(TextureInd::ACTIVE);
            board_->highlightEnemiesInRange(unit->getBox(),
                                            unit->getStats().attackRange);
            SDLAudioManager::getInstance()->setChannelVolume(30, 0);
            SDLAudioManager::getInstance()->playChannel(4, 0, 0);
          } else {
            advanceTurn();
          }
        });
  } else {
    std::cout << "Out of movement range!\n";
    SDLAudioManager::getInstance()->playChannel(3, 0, 0);
  }
}

void BoardController::onClickAttack(Box *boxClicked) {
  Unit *enemyUnit = boxClicked->getContent();
  if (enemyUnit != nullptr) {
    // Unit clicked if from a different team and in range
    if (enemyUnit->getTeam() != activeUnit_->getTeam() &&
        board_->isInRange(activeUnit_->getBox(), boxClicked,
                          activeUnit_->getStats().attackRange)) {
      // enemyUnit->loseHealth(activeUnit_->getAttack());
      activeUnit_->attack(enemyUnit, false);
      SDLAudioManager::getInstance()->playChannel(5, 0, 0);

      // Enemy dies
      if (enemyUnit->getStats().health == 0) {
        if (enemyUnit->getTeam()->getColor() == Color::RED) {
          GameManager::getInstance()->addMoney(enemyUnit->getStats().prize);
        }
        boxClicked->setContent(nullptr);
        turnBar_->eraseUnit(enemyUnit);
        scene_->removeGameObject(enemyUnit);
      }

      // Re-highlight board
      board_->resetCellsToBase();
      activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
      board_->highlightCellsInRange(activeUnit_->getBox(),
                                    activeUnit_->getStats().moveRange);
      hasAttacked_ = true;
    }

    // Unit dies to counter-attack
    if (activeUnit_->getStats().health == 0) {
      activeUnit_->getBox()->setContent(nullptr);
      turnBar_->eraseUnit(activeUnit_);
      scene_->removeGameObject(activeUnit_);
      advanceTurn();
    }
  }
}

void BoardController::advanceTurn() {
  board_->resetCellsToBase();
  hasMoved_ = hasAttacked_ = false;
  turnBar_->advanceTurn();
  activeUnit_ = turnBar_->getFrontUnit();

  activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
  board_->highlightCellsInRange(activeUnit_->getBox(),
                                activeUnit_->getStats().moveRange);
  board_->highlightEnemiesInRange(activeUnit_->getBox(),
                                  activeUnit_->getStats().attackRange);
}

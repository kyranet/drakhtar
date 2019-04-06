// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "BoardController.h"
#include "../GameObjects/Board.h"
#include "../GameObjects/Box.h"
#include "../GameObjects/TurnBar.h"
#include "../GameObjects/Unit.h"
#include "../Managers/SDLAudioManager.h"
#include "../Scenes/GameScene.h"
#include <iostream>

BoardController::BoardController(Board *board, TurnBar *turnBar,
                                 GameScene *scene)
    : board_(board), turnBar_(turnBar), scene_(scene), ListenerOnClick(board) {
  activeUnit_ = turnBar_->getFrontUnit();
  activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
  board_->highlightCellsInRange(activeUnit_->getBox(),
                                activeUnit_->getMoveRange());
  board_->highlightEnemiesInRange(activeUnit_->getBox(),
                                  activeUnit_->getAttackRange());
}

// Is called every time an event is captured
void BoardController::run(SDL_Event event) {
  // Captures mouse event
  ListenerOnClick::run(event);

  // If no actions left, reset and skip turn
  if (hasMoved && hasAttacked) {
    advanceTurn();
  }
}

void BoardController::onClickStop(SDL_Point point) {
  Box *boxClicked = board_->getBoxAtCoordinates(point);

  if (boxClicked != nullptr) {
    if (boxClicked->isEmpty() && !hasMoved) {
      onClickMove(boxClicked);
    } else if (!hasAttacked) {
      onClickAttack(boxClicked);
    }
  }
}

void BoardController::onClickMove(Box *boxClicked) {
  // Checks if the box clicked is within movement range
  if (board_->isInMoveRange(activeUnit_->getBox(), boxClicked,
                            activeUnit_->getMoveRange())) {
    board_->findPath(activeUnit_->getBox()->getIndex(), boxClicked->getIndex());
    activeUnit_->moveToBox(boxClicked);
    hasMoved = true;
    SDLAudioManager::getInstance()->playChannel(0, 0, 0);

    // If there are enemies in range, highlight them, otherwise skip turn
    if (board_->isEnemyInRange(boxClicked, activeUnit_->getAttackRange())) {
      board_->resetCellsToBase();
      activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
      board_->highlightEnemiesInRange(activeUnit_->getBox(),
                                      activeUnit_->getAttackRange());
	  SDLAudioManager::getInstance()->setChannelVolume(30,0);
      SDLAudioManager::getInstance()->playChannel(4, 0, 0);

    } else {
      advanceTurn();
    }
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
                          activeUnit_->getAttackRange())) {
      enemyUnit->loseHealth(activeUnit_->getAttack());
	  SDLAudioManager::getInstance()->playChannel(5, 0, 0);
      if (enemyUnit->getHealth() == 0) {
        boxClicked->setContent(nullptr);
        turnBar_->eraseUnit(enemyUnit);
        scene_->removeGameObject(enemyUnit);
      }
      hasAttacked = true;
    }
  }
}

void BoardController::advanceTurn() {
  board_->resetCellsToBase();
  hasMoved = hasAttacked = false;
  turnBar_->advanceTurn();
  activeUnit_ = turnBar_->getFrontUnit();
  activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
  board_->highlightCellsInRange(activeUnit_->getBox(),
                                activeUnit_->getMoveRange());
  board_->highlightEnemiesInRange(activeUnit_->getBox(),
                                  activeUnit_->getAttackRange());
}

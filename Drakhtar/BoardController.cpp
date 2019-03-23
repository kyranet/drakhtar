// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "BoardController.h"
#include <iostream>
#include "GameScene.h"
#include "TurnBar.h"
#include "Box.h"
#include "Unit.h"

BoardController::BoardController(Board* board, TurnBar* turnBar,
                                 GameScene* scene)
    : board_(board), turnBar_(turnBar), scene_(scene) {}

// Is called every time an event is captured
void BoardController::run(SDL_Event event) {
  activeUnit_ = turnBar_->getFrontUnit();

  // Highlights cells around selected unit
  activeUnit_->getBox()->setCurrentTexture(TextureInd::ACTIVE);
  if (!hasMoved) {
    board_->highlightCellsInRange(activeUnit_->getBox(),
                                  activeUnit_->getMoveRange());
  }
  if (!hasAttacked) {
    board_->highlightEnemiesInRange(activeUnit_->getBox(),
                                    activeUnit_->getAttackRange());
  }

  // Captures mouse event
  if (event.type == SDL_MOUSEBUTTONUP) {
    SDL_Point p = {event.motion.x, event.motion.y};
    Box* boxClicked = board_->getBoxAtCoordinates(Vector2D<int>(p.x, p.y));

    if (boxClicked != nullptr) {
      if (boxClicked->isEmpty() && !hasMoved) {
        onClickMove(boxClicked);
      } else if (!hasAttacked) {
        onClickAttack(boxClicked);
      }
    }
  }

  // If no actions left, reset and skip turn
  if (hasMoved && hasAttacked) {
    hasMoved = hasAttacked = false;
    turnBar_->advanceTurn();
  }
}

void BoardController::onClickMove(Box* boxClicked) {
  // Checks if the box clicked is within movement range
  if (board_->isInRange(activeUnit_->getBox(), boxClicked,
                        activeUnit_->getMoveRange())) {
    activeUnit_->moveToBox(boxClicked);
    hasMoved = true;
    board_->resetCellsToBase();

    // If there are no enemies in range, reset and skip turn
    if (!board_->isEnemyInRange(boxClicked, activeUnit_->getAttackRange())) {
      hasMoved = hasAttacked = false;
      turnBar_->advanceTurn();
    }
  } else {
    cout << "Out of movement range!" << endl;
  }
}

void BoardController::onClickAttack(Box* boxClicked) {
  Unit* enemyUnit = boxClicked->getContent();

  // Unit clicked if from a different team and in range
  if (enemyUnit->getTeam() != activeUnit_->getTeam() &&
      board_->isInRange(activeUnit_->getBox(), boxClicked,
                        activeUnit_->getAttackRange())) {
    enemyUnit->loseHealth(activeUnit_->getAttack());
    if (enemyUnit->getHealth() == 0) {
      boxClicked->setContent(nullptr);
      turnBar_->eraseUnit(enemyUnit);
      scene_->removeGameObject(enemyUnit);
    }
    hasAttacked = true;
    board_->resetCellsToBase();
  }
}

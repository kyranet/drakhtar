// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitsController.h"
#include "GameObjects/Board.h"
#include "GameObjects/TurnBar.h"

UnitsController::UnitsController(Board* board, TurnBar* turnBar,
                                 GameScene* scene)
    : board_(board), turnBar_(turnBar), scene_(scene) {
  activeUnit_ = turnBar_->getTurnFor();
}
Board* UnitsController::getBoard() { return board_; }

TurnBar* UnitsController::getTurnBar() { return turnBar_; }

Unit* UnitsController::getActiveUnit() { return activeUnit_; }

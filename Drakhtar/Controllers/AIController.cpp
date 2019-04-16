// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "AIController.h"
#include "GameObjects/TurnBar.h"

AIController::AIController(Board* board, TurnBar* turnBar, GameScene* scene)
    : UnitsController(board, turnBar, scene) {}

void AIController::run() {}

void AIController::advanceTurn() {
  hasMoved_ = hasAttacked_ = false;
  turnBar_->advanceTurn();
  activeUnit_ = turnBar_->getFrontUnit();
}

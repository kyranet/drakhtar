// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TeamController.h"
#include "GameObjects/Board.h"
#include "GameObjects/TurnBar.h"

TeamController::TeamController(Board *board, TurnBar *turnBar, GameScene *scene)
    : board_(board), turnBar_(turnBar), scene_(scene), ListenerOnClick(board) {
  activeUnit_ = turnBar_->getFrontUnit();
}

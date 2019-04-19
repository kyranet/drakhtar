// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "AIController.h"
#include "GameObjects/TurnBar.h"

AIController::AIController(Board* board, TurnBar* turnBar, GameScene* scene)
    : UnitsController(board, turnBar, scene) {}

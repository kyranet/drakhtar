// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "AIController.h"
#include "GameObjects/TurnBar.h"

AIController::AIController(Board* board, TurnBar* turnBar, GameScene* scene,
                           Team* team, Team* oppositeTeam)
    : UnitsController(board, turnBar, scene, team, oppositeTeam) {}


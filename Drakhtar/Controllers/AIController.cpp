// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "AIController.h"

#include "GameObjects/TurnBar.h"

AIController::AIController(Board* board, TurnManager* turnManager,
                           GameScene* scene, Team* team, Team* oppositeTeam)
    : UnitsController(board, turnManager, scene, team, oppositeTeam) {}

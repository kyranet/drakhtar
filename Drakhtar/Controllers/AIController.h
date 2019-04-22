// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "UnitsController.h"

class AIController final : public UnitsController {
 public:
  AIController(Board* board, TurnManager* turnManager, GameScene* scene,
               Team* team, Team* oppositeTeam);
};

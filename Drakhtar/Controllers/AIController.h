// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "UnitsController.h"

class AIController final : public UnitsController {
  int minimax(int depth, int alpha, int beta, bool isMaximisingPlayer,
              bool hasMoved, bool hasAttacked) const;
  int evaluateBoard() const;

 public:
  AIController(Board* board, GameScene* scene, Team* team, Team* oppositeTeam);
  void start() override;
};

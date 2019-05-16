// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "AIController.h"
#include "GameObjects/Box.h"
#include "GameObjects/TurnBar.h"
#include "GameObjects/Unit.h"
#include "Managers/State.h"

AIController::AIController(Board* board, GameScene* scene, Team* team,
                           Team* oppositeTeam)
    : UnitsController(board, scene, team, oppositeTeam) {}

int AIController::minimax(int depth, int alpha, int beta,
                          bool isMaximisingPlayer) const {
  if (depth == 0) {
    return -evaluateBoard();
  }

  const auto state = getState();
  const auto unit = getActiveUnit();
  const auto position = unit->getBox()->getIndex();
  const auto stats = state->getModifiedAt(position);
  if (isMaximisingPlayer) {
    int bestMove = -9999;
    for (const auto& move :
         state->getCellsInMovementRange(position, stats.moveRange_)) {
      state->save();
      state->move(position, move);
      bestMove = std::max(bestMove,
                          minimax(depth - 1, alpha, beta, !isMaximisingPlayer));
      state->restore();
      alpha = std::max(alpha, bestMove);
      if (beta <= alpha) {
        return bestMove;
      }
    }
    return bestMove;
  } else {
    int bestMove = 9999;
    for (const auto& move :
         state->getCellsInMovementRange(position, stats.moveRange_)) {
      state->save();
      state->move(position, move);
      bestMove = std::min(bestMove,
                          minimax(depth - 1, alpha, beta, !isMaximisingPlayer));
      state->restore();
      beta = std::min(beta, bestMove);
      if (beta <= alpha) {
        return bestMove;
      }
    }
    return bestMove;
  }
}

int AIController::evaluateBoard() const {
  const auto state = getState();
  const auto team = getActiveUnit()->getTeam()->getColor();

  int evaluation = 0;
  for (const auto& stats : state->getBoard()) {
    if (stats.unit_ == nullptr) continue;
    evaluation += stats.team_ == team ? stats.prize_ : -stats.prize_;
  }

  return evaluation;
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "AIController.h"
#include "GameObjects/Box.h"
#include "GameObjects/Commanders/Commander.h"
#include "GameObjects/Skill.h"
#include "GameObjects/TurnBar.h"
#include "GameObjects/Unit.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/State.h"
#include "Structures/Texture.h"

AIController::AIController(Board* board, GameScene* scene, Team* team,
                           Team* oppositeTeam)
    : UnitsController(board, scene, team, oppositeTeam) {}

int AIController::minimax(int depth, int alpha, int beta,
                          bool isMaximisingPlayer, bool hasMoved,
                          bool hasAttacked) const {
  if (depth == 0) {
    return -evaluateBoard();
  }

  const auto state = getState();
  const auto unit = getActiveUnit();
  const auto position = unit->getBox()->getIndex();
  const auto stats = state->getModifiedAt(position);
  if (isMaximisingPlayer) {
    // Player playing
    int bestMove = -9999999;
    if (!hasMoved) {
      for (const auto& move :
           state->getCellsInMovementRange(position, stats.moveRange_)) {
        state->save();
        state->move(position, move);
        bestMove =
            std::max(bestMove, minimax(depth - 1, alpha, beta,
                                       isMaximisingPlayer, true, hasAttacked));
        state->restore();
        alpha = std::max(alpha, bestMove);
        if (beta <= alpha) {
          return bestMove;
        }
      }
      hasMoved = true;
    }

    if (!hasAttacked) {
      for (const auto& attack : state->getCellsInAttackRange(
               position, oppositeTeam_->getColor(), stats.attackRange_)) {
        state->save();
        state->attack(position, attack);
        bestMove =
            std::max(bestMove, minimax(depth - 1, alpha, beta,
                                       !isMaximisingPlayer, hasMoved, true));
        state->restore();
        alpha = std::max(alpha, bestMove);
        if (beta <= alpha) {
          return bestMove;
        }
      }
    }

    return bestMove;
  } else {
    // AI playing
    int bestMove = 9999999;
    if (!hasMoved) {
      for (const auto& move :
           state->getCellsInMovementRange(position, stats.moveRange_)) {
        state->save();
        state->move(position, move);
        bestMove =
            std::min(bestMove, minimax(depth - 1, alpha, beta,
                                       isMaximisingPlayer, true, hasAttacked));
        state->restore();
        beta = std::min(beta, bestMove);
        if (beta <= alpha) {
          return bestMove;
        }
      }
      hasMoved = true;
    }

    if (!hasAttacked) {
      for (const auto& attack : state->getCellsInAttackRange(
               position, team_->getColor(), stats.attackRange_)) {
        state->save();
        state->attack(position, attack);
        bestMove =
            std::min(bestMove, minimax(depth - 1, alpha, beta,
                                       !isMaximisingPlayer, hasMoved, true));
        state->restore();
        beta = std::min(beta, bestMove);
        if (beta <= alpha) {
          return bestMove;
        }
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
    evaluation += stats.team_ == team ? stats.prize_ * stats.health_
                                      : -stats.prize_ * stats.health_;
  }

  return evaluation;
}

void AIController::start() {
  UnitsController::start();
  if (!activeUnit_) return UnitsController::finish();

  // Always use all available skills
  if (activeUnit_->isCommander()) {
    for (auto skill : reinterpret_cast<Commander*>(activeUnit_)->getSkills()) {
      if (skill->getRemainingCooldown() == 0) {
        skill->cast();
      }
    }
  }

  // Set this controller
  getState()->setController(this);

  const auto state = getState();
  const auto position = activeUnit_->getBox()->getIndex();
  const auto stats = state->getModifiedAt(position);

  auto bestMove = -9999999;
  Vector2D<uint16_t> bestMoveFound(1000, 1000);
  for (const auto& move :
       state->getCellsInMovementRange(position, stats.moveRange_)) {
    state->save();
    state->move(position, move);
    const auto value = minimax(6, -9999999, 9999999, true, true, false);
    state->restore();
    if (value >= bestMove) {
      bestMove = value;
      bestMoveFound.set(move);
    }
  }

  hasMoved_ = bestMoveFound.getX() != 1000;
  if (hasMoved_) {
    move(position, bestMoveFound);
  } else {
    tryAttack();
  }
}

void AIController::tryAttack() {
  const auto state = getState();
  const auto position = activeUnit_->getBox()->getIndex();
  const auto stats = state->getModifiedAt(position);

  auto bestAttack = -9999999;
  Vector2D<uint16_t> bestAttackFound(1000, 1000);
  for (const auto& move : state->getCellsInAttackRange(
           position, team_->getColor(), stats.attackRange_)) {
    state->save();
    state->move(position, move);
    const auto value = minimax(5, -9999999, 9999999, true, hasMoved_, false);
    state->restore();
    if (value >= bestAttack) {
      bestAttack = value;
      bestAttackFound.set(move);
    }
  }

  if (bestAttackFound.getX() != 1000) {
    activeUnit_->getTexture()->setAnimationOnce("attack");
    SDLAudioManager::getInstance()->playChannel(5, 0, 0);
    state->attack(position, bestAttackFound);
  }

  finish();
}

void AIController::onComplete() {
  UnitsController::onComplete();
  tryAttack();
}

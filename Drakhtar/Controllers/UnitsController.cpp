// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitsController.h"

#include "Errors/DrakhtarError.h"
#include "EventListeners/EventListener.h"
#include "GameObjects/Board.h"
#include "GameObjects/Unit.h"
#include "Managers/TurnManager.h"
#include "Structures/Team.h"

UnitsController::UnitsController(Board* board, TurnManager* turnManager,
                                 GameScene* scene, Team* team,
                                 Team* oppositeTeam)
    : board_(board),
      turnManager_(turnManager),
      scene_(scene),
      team_(team),
      oppositeTeam_(oppositeTeam) {}

UnitsController::~UnitsController() = default;

void UnitsController::start() {
  // Reset this controller's state
  hasAttacked_ = false;
  hasMoved_ = false;

  // Deactivate all listeners
  for (auto& listener : listeners_) listener->setActive(true);
  activeUnit_ = turnManager_->getTurnFor();
}

void UnitsController::finish() {
  for (auto& listener : listeners_) listener->setActive(false);
  activeUnit_ = nullptr;

  // Update the turn bar
  turnManager_->next();

  if (turnManager_->getTurnFor()->getTeam() != oppositeTeam_) return start();

  // Once this controller is finished, start the controller of the opposite
  // team.
  oppositeTeam_->getController()->start();
}

Board* UnitsController::getBoard() const { return board_; }
TurnManager* UnitsController::getTurnManager() const { return turnManager_; }
Unit* UnitsController::getActiveUnit() const { return activeUnit_; }
bool UnitsController::hasAttacked() const { return hasAttacked_; }
bool UnitsController::hasMoved() const { return hasMoved_; }

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitsController.h"
#include "EventListeners/EventListener.h"
#include "GameObjects/Board.h"
#include "GameObjects/TurnBar.h"
#include "Structures/Team.h"

UnitsController::UnitsController(Board* board, TurnBar* turnBar,
                                 GameScene* scene, Team* team,
                                 Team* oppositeTeam)
    : board_(board),
      turnBar_(turnBar),
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
  activeUnit_ = turnBar_->getTurnFor();
}

void UnitsController::finish() {
  for (auto& listener : listeners_) listener->setActive(false);
  activeUnit_ = nullptr;

  // Update the turn bar
  turnBar_->next();

  // Once this controller is finished, start the controller of the opposite
  // team.
  oppositeTeam_->getController()->start();
}

Board* UnitsController::getBoard() const { return board_; }
TurnBar* UnitsController::getTurnBar() const { return turnBar_; }
Unit* UnitsController::getActiveUnit() const { return activeUnit_; }
bool UnitsController::hasAttacked() const { return hasAttacked_; }
bool UnitsController::hasMoved() const { return hasMoved_; }

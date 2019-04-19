// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitsController.h"
#include "EventListeners/EventListener.h"
#include "GameObjects/Board.h"
#include "GameObjects/TurnBar.h"

UnitsController::UnitsController(Board* board, TurnBar* turnBar,
                                 GameScene* scene)
    : board_(board), turnBar_(turnBar), activeUnit_(nullptr), scene_(scene) {}

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
}

Board* UnitsController::getBoard() { return board_; }
TurnBar* UnitsController::getTurnBar() { return turnBar_; }
Unit* UnitsController::getActiveUnit() { return activeUnit_; }

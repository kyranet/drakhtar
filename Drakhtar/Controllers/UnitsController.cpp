// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitsController.h"
#include "Errors/DrakhtarError.h"
#include "EventListeners/EventListener.h"
#include "GameObjects/Board.h"
#include "GameObjects/Unit.h"
#include "Managers/State.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"

UnitsController::UnitsController(Board* board, GameScene* scene, Team* team,
                                 Team* oppositeTeam)
    : board_(board), scene_(scene), team_(team), oppositeTeam_(oppositeTeam) {}

UnitsController::~UnitsController() = default;

void UnitsController::start() {
  // Reset this controller's state
  hasAttacked_ = false;
  hasMoved_ = false;

  // Deactivate all listeners
  for (auto& listener : listeners_) listener->setActive(true);
  activeUnit_ = getState()->getActiveUnit();
  activeUnit_->onSelect();
}

void UnitsController::finish() {
  if (activeUnit_ != nullptr) {
    activeUnit_->onDeselect();
    for (auto& listener : listeners_) listener->setActive(false);
    activeUnit_ = nullptr;
  }

  // Update the turn bar
  const auto state = getState();
  state->next();

  if (state->getActiveUnit()->getTeam() == team_) {
    getBoard()->getScene()->processNextTick([this]() { start(); });
  } else {
    // Once this controller is finished, start the controller of the opposite
    // team.
    getBoard()->getScene()->processNextTick(
        [this]() { oppositeTeam_->getController()->start(); });
  }
}

Board* UnitsController::getBoard() const { return board_; }
Unit* UnitsController::getActiveUnit() const { return activeUnit_; }
State* UnitsController::getState() const {
  return reinterpret_cast<GameScene*>(getBoard()->getScene())->getState();
}
bool UnitsController::hasAttacked() const { return hasAttacked_; }
bool UnitsController::hasMoved() const { return hasMoved_; }

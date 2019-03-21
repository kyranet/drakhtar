// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Board.h"
#include "EventListener.h"
#include "GameState.h"
#include "SDL.h"
#include "TurnBar.h"

class BoardController : public EventListener {
 protected:
  Board *board_;
  TurnBar *turnBar_;
  Unit *activeUnit_;
  GameState *state_;
  bool hasMoved = false;
  bool hasAttacked = false;

 public:
  BoardController(Board *board, TurnBar *turnBar, GameState *state);

  // Is called from GameState::_handleEvents() any time an event is captured
  virtual void run(SDL_Event event);

  // Moves turnBar's current unit to an empty cell within range
  void onClickMove(Box *boxClicked);

  // turnBar's current unit attacks target enemy unit in range
  void onClickAttack(Box *boxClicked);
};

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "SDL.h"
#include "EventListener.h"
#include "Board.h"
#include "TurnBar.h"
#include "State.h"

class BoardController : public EventListener
{
 protected:
    Board *board_;
    TurnBar *turnBar_;
    Unit *activeUnit_;
    bool hasMoved = false;
	bool hasAttacked = false;

 public:
    BoardController(Board *board, TurnBar *turnBar);

	// Is called from GameState::_handleEvents() any time an event is captured
    virtual void run(SDL_Event event);

	// Moves turnBar's current unit to an empty cell within range
	void onClickMove(Box* boxClicked);

	// turnBar's current unit attacks target enemy unit in range
    void onClickAttack(Box* boxClicked);
};

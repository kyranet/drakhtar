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
    bool moving = true;

 public:
    BoardController(Board *board, TurnBar *turnBar);
    virtual void run(SDL_Event event);
    void onClickMove(SDL_Point p);
    void onClickAttack(SDL_Point p);
};

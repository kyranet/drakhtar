// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "ListenerOnClick.h"
#include "SDL.h"

class TurnBar;
class Unit;
class GameScene;
class Board;
class Box;

class BoardController : public ListenerOnClick {
 protected:
  Board *board_;
  TurnBar *turnBar_;
  Unit *activeUnit_;
  GameScene *scene_;
  bool hasMoved = false;
  bool hasAttacked = false;
  bool isTweening = false;

 public:
  BoardController(Board *board, TurnBar *turnBar, GameScene *scene);

  void run(SDL_Event event);
  void onClickStop(SDL_Point point);

  // Moves turnBar's current unit to an empty cell within range
  void onClickMove(Box *boxClicked);

  // turnBar's current unit attacks target enemy unit in range
  void onClickAttack(Box *boxClicked);

  // Activates next unit
  void advanceTurn();
};

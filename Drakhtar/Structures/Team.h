// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <list>
#include "../GameObjects/Board.h"
#include "../GameObjects/Unit.h"

class Unit;

enum Color { BLUE, RED };

class Team {
  std::list<Unit *> units_;
  Board *board_ = nullptr;
  std::list<Unit *>::iterator findInsertPosition(Unit *unit);
  Color color_;

 public:
  Team(Board *board, Color color);
  virtual ~Team();
  Board *getBoard() const;
  void addUnit(Unit *unit);
  void removeUnit(Unit *unit);
  Unit *pickUnit() const;
  std::list<Unit *> getUnitList() const;
  Color getColor() const;
};

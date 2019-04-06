// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <list>
#include "../GameObjects/Board.h"
#include "../GameObjects/Unit.h"

class Unit;
class Commander;

enum Color { BLUE, RED };

class Team {
  std::list<Unit *> units_;
  Board *board_ = nullptr;
  std::list<Unit *>::iterator findInsertPosition(Unit *unit);
  Color color_;
  Commander *commander_ = nullptr;

 public:
  Team(Board *board, Color color);
  virtual ~Team();
  Board *getBoard() const;
  Commander *getCommander() const { return commander_; }
  void setCommander(Commander* commander) { commander_ = commander; }
  void addUnit(Unit *unit);
  void removeUnit(Unit *unit);
  Unit *pickUnit() const;
  std::list<Unit *> getUnitList() const;
  Color getColor() const;
};

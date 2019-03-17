// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <list>
#include "Unit.h"
#include "Board.h"

class Unit;

enum Color
{
    BLUE,
    RED
};

class Team
{
 private:
    list<Unit *> units_;
    Board *board_ = nullptr;
    list<Unit *>::iterator findInsertPosition(Unit *unit);
    Color color_;

 public:
    Team(Board *board, Color color);
    virtual ~Team();
    Board *getBoard() { return board_; }
    void addUnit(Unit *unit);
    void removeUnit(Unit *unit);
    Unit *pickUnit() const;
    list<Unit *> getUnitList() { return units_; }
    Color getColor();
};

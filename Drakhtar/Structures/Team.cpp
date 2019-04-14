// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Team.h"
#include "../Errors/TeamedUnitError.h"

Team::Team(Board *board, const Color color) : board_(board), color_(color) {}

Team::~Team() { board_ = nullptr; }

Board *Team::getBoard() const { return board_; }

void Team::addUnit(Unit *unit) {
  if (unit->getTeam() != nullptr) {
    throw TeamedUnitError("This unit already has a team.");
  }
  unit->setTeam(this);

  // Gets the sorted position. If it does not find an unit
  // with lower speed, it gets pushed to the end, otherwise
  // it gets pushed right before the first slower one.
  const auto index = findInsertPosition(unit);
  if (index == units_.end())
    units_.push_back(unit);
  else
    units_.insert(index, unit);
}

void Team::removeUnit(Unit *unit) {
  units_.remove(unit);
  delete unit;
}

Unit *Team::pickUnit() const {
  if (units_.empty()) return nullptr;

  for (auto unit : units_) {
    if (!unit->getMoved()) {
      unit->setMoving(true);
      return unit;
    }
  }

  for (auto unit : units_) unit->setMoved(false);

  auto unit = units_.front();
  unit->setMoving(true);
  return unit;
}

std::list<Unit *> Team::getUnitList() const { return units_; }

Color Team::getColor() const { return color_; }

std::list<Unit *>::iterator Team::findInsertPosition(Unit *) {
  // auto i = 0;
  // auto it = units_.begin();
  auto end = units_.end();
  /*
  while (it != end)
  {
      if (unit->getSpeed() > (*it)->getSpeed()) return it;
      i++;
  }
  */
  return end;
}

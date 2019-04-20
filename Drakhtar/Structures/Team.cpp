// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Team.h"
#include <algorithm>
#include "Controllers/UnitsController.h"
#include "Errors/TeamedUnitError.h"
#include "GameObjects/Commanders/Commander.h"
#include "GameObjects/Unit.h"

Team::Team(const Color color) : color_(color) {}

Team::~Team() { delete controller_; }

Color Team::getColor() const { return color_; }

void Team::addUnit(Unit* unit) {
  if (unit->getTeam() != nullptr) {
    throw TeamedUnitError("This unit already has a team.");
  }
  units_.push_back(unit);
  unit->setTeam(this);
}

void Team::removeUnit(Unit* unit) {
  for (auto it = units_.begin(), end = units_.end(); it != end; ++it) {
    if (*it != unit) continue;
    units_.erase(it);
    break;
  }
}

std::vector<Unit*> Team::getUnits() const { return units_; }

void Team::addCommander(Commander* commander) {
  commanders_.push_back(commander);
}

void Team::removeCommander(Commander* commander) {
  for (auto it = commanders_.begin(), end = commanders_.end(); it != end;
       ++it) {
    if (*it != commander) continue;
    commanders_.erase(it);
    break;
  }
}

std::vector<Commander*> Team::getCommanders() const { return commanders_; }

void Team::sortUnits() {
  std::sort(units_.begin(), units_.end(), [](Unit* a, Unit* b) {
    return a->getBaseStats().speed > b->getBaseStats().speed;
  });
}

void Team::setController(UnitsController* controller) {
  controller_ = controller;
}

UnitsController* Team::getController() const { return controller_; }

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Commander.h"

Commander::Commander(Scene *scene, Texture *texture, Box *box,
                     const UnitStats commanderStats)
    : Unit(scene, texture, box, commanderStats, "") {}

Commander::~Commander() {
  for (auto skill : skills_) {
    delete skill;
  }
  skills_.clear();
}

void Commander::onSelect() {
  Unit::onSelect();
  for (auto skill : skills_) {
    // Lowers skill cooldown timer
    if (skill->getRemainingCooldown() > 0) {
      skill->setRemainingCooldown(skill->getRemainingCooldown() - 1);
    }

    // Lowers skill duration timer
    if (skill->getRemainingDuration() > 0) {
      skill->setRemainingDuration(skill->getRemainingDuration() - 1);
    }

    // Ends skill if it was active and its duration finished
    if (skill->getActive() && skill->getRemainingDuration() == 0) {
      skill->end();
    }
  }
}

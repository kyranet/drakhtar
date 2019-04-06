// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Commander.h"

Commander::Commander(Scene *scene, Texture *texture, Box *box, int attack,
                     int defense, int health, int speed, int attackRange,
                     int moveRange, int prize)
    : Unit(scene, texture, box, attack, defense, health, speed, attackRange,
           moveRange, prize) {}

Commander::~Commander() {
  for (auto skill : skills) {
    delete skill;
  }
  skills.clear();
}

void Commander::onSelect() {
  Unit::onSelect();
  for (auto skill : skills) {
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

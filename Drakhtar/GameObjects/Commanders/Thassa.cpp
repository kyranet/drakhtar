// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Thassa.h"

Thassa::Thassa(Scene *scene, Texture *texture, Box *box, int attack,
               int defense, int health, int speed, int attackRange,
               int moveRange, int prize)
    : Commander(scene, texture, box, attack, defense, health, speed,
                attackRange, moveRange, prize) {
  skills.push_back(new BattleCry(this));
}
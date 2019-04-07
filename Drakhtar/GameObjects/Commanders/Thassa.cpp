// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Thassa.h"

Thassa::Thassa(Scene *scene, Texture *texture, Box *box, const int attack,
               const int defense, const int health, const int speed,
               const int attackRange, const int moveRange, const int prize)
    : Commander(scene, texture, box, attack, defense, health, speed,
                attackRange, moveRange, prize) {
  skills_.push_back(new BattleCry(this));
}

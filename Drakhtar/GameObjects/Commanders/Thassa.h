// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Commander.h"

class Scene;

class Thassa final : public Commander {
 public:
  Thassa(Scene* scene, Texture* texture, Box* box, int attack, int defense,
         int health, int speed, int attackRange, int moveRange, int prize);
};

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <vector>
#include "../Skill.h"
#include "Commander.h"

class Scene;

class Thassa : public Commander {
 public:
  Thassa(Scene* scene, Texture* texture, Box* box, int attack, int defense,
         int health, int speed, int attackRange, int moveRange, int prize);
  virtual ~Thassa();
};

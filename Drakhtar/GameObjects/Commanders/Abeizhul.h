// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Commander.h"

class Scene;

class Abeizhul final : public Commander {
 public:
  Abeizhul(Scene* scene, Texture* texture, Box* box, UnitStats abeizhulstats);
};

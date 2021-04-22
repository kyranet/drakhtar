// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Commander.h"

class Scene;

class Sheissah final : public Commander {
 public:
  Sheissah(Scene* scene, Texture* texture, Box* box, UnitStats sheissahStats);
};

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Commander.h"

class Scene;

class Valar final : public Commander {
 public:
  Valar(Scene* scene, Texture* texture, Box* box, UnitStats valarStats);
};

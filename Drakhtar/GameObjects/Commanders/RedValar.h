// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Commander.h"

class Scene;

class RedValar final : public Commander {
 public:
  RedValar(Scene* scene, Texture* texture, Box* box, UnitStats valarStats);
};

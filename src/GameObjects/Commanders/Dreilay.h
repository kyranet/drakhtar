// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Commander.h"

class Scene;

class Dreilay final : public Commander {
 public:
  Dreilay(Scene* scene, Texture* texture, Box* box, UnitStats dreilayStats);
};

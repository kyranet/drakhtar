// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Commander.h"

class Scene;

class Thassa final : public Commander {
public:
  Thassa(Scene *scene, Texture *texture, Box *box, UnitStats thassaStats);
};

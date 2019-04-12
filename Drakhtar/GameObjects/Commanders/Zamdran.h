// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Commander.h"

class Scene;

class Zamdran final : public Commander {
 public:
  Zamdran(Scene *scene, Texture *texture, Box *box, UnitStats Zamdranstats);
};

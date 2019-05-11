// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "RedValar.h"

RedValar::RedValar(Scene* scene, Texture* texture, Box* box,
             const UnitStats valarStats)
    : Commander("Valar", scene, texture, box, valarStats) {
  size_.setX(WIN_WIDTH / 6.4f);
  size_.setY(WIN_HEIGHT / 3.6f);
  skills_.push_back(new Berserker(this));
}

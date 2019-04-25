// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Sheissah.h"

Sheissah::Sheissah(Scene* scene, Texture* texture, Box* box,
                   const UnitStats sheissahStats)
    : Commander("Sheissah", scene, texture, box, sheissahStats) {
  skills_.push_back(new WitheringCurse(this));
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Dreilay.h"

Dreilay::Dreilay(Scene* scene, Texture* texture, Box* box,
                   const UnitStats dreilayStats)
    : Commander("Dreilay", scene, texture, box, dreilayStats) {
  skills_.push_back(new Charge(this));
}

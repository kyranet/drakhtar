// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Abeizhul.h"

Abeizhul::Abeizhul(Scene* scene, Texture* texture, Box* box,
                   const UnitStats abeizhulStats)
    : Commander("Abeizhul", scene, texture, box, abeizhulStats) {
  skills_.push_back(new WitheringCurse(this));
}

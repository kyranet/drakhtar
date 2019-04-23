// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Thassa.h"

Thassa::Thassa(Scene *scene, Texture *texture, Box *box,
               const UnitStats thassaStats)
    : Commander(scene, texture, box, thassaStats) {
  skills_.push_back(new BattleCry(this));
  skills_.push_back(new HeroicStrike(this));
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Zamdran.h"

Zamdran::Zamdran(Scene *scene, Texture *texture, Box *box, const  UnitStats Zamdranstats)
    : Commander(scene, texture, box, Zamdranstats) {
  skills_.push_back(new ArrowRain(this));
}

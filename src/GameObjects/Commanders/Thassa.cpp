// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Thassa.h"

#include "Managers/SDLAudioManager.h"
Thassa::Thassa(Scene* scene, Texture* texture, Box* box,
               const UnitStats thassaStats)
    : Commander("Thassa", scene, texture, box, thassaStats) {
  size_.setX(WIN_WIDTH / 8);
  size_.setY(static_cast<int>(WIN_HEIGHT / 4.5));
  skills_.push_back(new BattleCry(this));
  skills_.push_back(new HeroicStrike(this));
}

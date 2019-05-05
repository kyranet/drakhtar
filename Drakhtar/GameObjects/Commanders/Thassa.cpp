// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Thassa.h"

#include "Managers/SDLAudioManager.h"
Thassa::Thassa(Scene* scene, Texture* texture, Box* box,
               const UnitStats thassaStats)
    : Commander("Thassa", scene, texture, box, thassaStats) {
  skills_.push_back(new BattleCry(this));
  skills_.push_back(new HeroicStrike(this));
}

void Thassa::attack(Unit* enemy, bool allowsCounter) {
  Commander::attack(enemy, allowsCounter);
  if (getUnstoppable()) SDLAudioManager::getInstance()->playChannel(9, 0, 1);
}

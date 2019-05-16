// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Abeizhul.h"
#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "Managers/State.h"
#include "Scenes/GameScene.h"

Abeizhul::Abeizhul(Scene* scene, Texture* texture, Box* box,
                   const UnitStats abeizhulStats)
    : Commander("Abeizhul", scene, texture, box, abeizhulStats) {
  skills_.push_back(new DeathRay(this));
  skills_.push_back(new Reinforce(this));
  // TODO(kyranet): Add modifier to move Abeizhul when attacked
}

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
}

// Move two boxes backwards when receiving damage
int Abeizhul::loseHealth(int enemyAttack, int minDamage) {
  const auto scene = reinterpret_cast<GameScene*>(getScene());
  const auto state = scene->getState();
  const auto stats = state->getAt(getBox()->getIndex());

  if (stats.health_ - enemyAttack > 0) {
    Vector2D<uint16_t> newIndex{static_cast<uint16_t>(box_->getIndex().getX() + 2),
                            box_->getIndex().getY()};
    const auto board = reinterpret_cast<GameScene*>(scene_)->getBoard();
    if (box_->getIndex().getX() + 2 < board->getCols()) {
      const auto next = state->getAt(newIndex);
      if (next.unit_ == nullptr) {
        moveToBox(
            board->getBoxAt(next.position_.getX(), next.position_.getY()));
      }
    }
  }
  return Unit::loseHealth(enemyAttack, minDamage);
}

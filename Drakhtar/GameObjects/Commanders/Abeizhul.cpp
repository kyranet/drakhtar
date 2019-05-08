// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Abeizhul.h"

#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "Scenes/GameScene.h"

Abeizhul::Abeizhul(Scene* scene, Texture* texture, Box* box,
                   const UnitStats abeizhulStats)
    : Commander("Abeizhul", scene, texture, box, abeizhulStats) {
  skills_.push_back(new DeathRay(this));
  skills_.push_back(new Reinforce(this));
}

// Move two boxes backwards when receiving damage
int Abeizhul::loseHealth(int enemyAttack, int minDamage) {
  Vector2D<int> newIndex = {box_->getIndex().getX() + 2,
                            box_->getIndex().getY()};
  Board* board = reinterpret_cast<GameScene*>(scene_)->getBoard();
  if (box_->getIndex().getX() + 2 < board->getCols()) {
    Box* newBox = board->getBoxAt(newIndex.getX(), newIndex.getY());
    if (newBox->getContent() == nullptr) {
      moveToBox(newBox);
    }
  }
  return Unit::loseHealth(enemyAttack, minDamage);
}

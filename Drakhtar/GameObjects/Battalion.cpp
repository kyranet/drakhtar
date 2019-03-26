// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Battalion.h"
#include "../Managers/FontManager.h"
#include "../Scenes/Scene.h"
#include "Box.h"
#include "Text.h"

Battalion::Battalion(Scene *scene, Texture *texture, Box *box, int attack,
                     int defense, int health, int speed, int attackRange,
                     int moveRange, int prize, int battalionSize)
    : Unit(scene, texture, box, attack, defense, health, speed, attackRange,
           moveRange, prize),
      battalionSize_(battalionSize) {
  health_ = Unit::getMaxHealth() * battalionSize_;

  SDL_Color textColor = {255, 255, 255, 255};

  healthText_->setText(healthToString());

  auto rect = box_->getRect();

  sizeText_ = new Text(scene, FontManager::get("Retron2000"),
                       {rect.x + rect.w / 2, rect.y + rect.h * 5 / 6},
                       textColor, sizeToString(), rect.w * 2);
}

Battalion::~Battalion() {
  if (sizeText_ != nullptr) {
    delete sizeText_;
    sizeText_ = nullptr;
  }
}

std::string Battalion::sizeToString() const {
  return std::to_string(battalionSize_);
}

void Battalion::setBattalionSize(int battalionSize) {
  battalionSize_ = battalionSize;
  sizeText_->setText(sizeToString());
}

int Battalion::getAttack() const { return Unit::getAttack() * battalionSize_; }

int Battalion::getMaxHealth() const {
  return Unit::getMaxHealth() * battalionSize_;
}

int Battalion::loseHealth(int attack) {
  int health = Unit::loseHealth(attack);
  if (Unit::getMaxHealth() <= health) {
    battalionSize_ -= health / Unit::getMaxHealth();
    if (battalionSize_ < 0) battalionSize_ = 0;
    sizeText_->setText(sizeToString());
  }
  return health;
}

void Battalion::moveToBox(Box *box) {
  Unit::moveToBox(box);

  auto rect = box_->getRect();

  sizeText_->setPosition(
      Vector2D<int>(rect.x + rect.w / 2, rect.y + rect.h * 4 / 5));
}

void Battalion::render() const {
  Unit::render();
  sizeText_->render();
}

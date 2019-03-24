// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Battalion.h"
#include "../Managers/FontManager.h"
#include "../Scenes/Scene.h"
#include "Box.h"
#include "Text.h"

Battalion::Battalion(Scene *scene, Texture *texture, Box *box, int attack,
                     int health, int speed, int attackRange, int moveRange,
                     int battalionSize)
    : Unit(scene, texture, box, attack, health, speed, attackRange, moveRange),
      battalionSize_(battalionSize) {
  health_ = Unit::getMaxHealth() * battalionSize_;

  SDL_Color textColor = {255, 255, 255, 255};

  healthText_->setText("Salud: " + std::to_string(this->getHealth()));

  auto rect = box_->getRect();

  sizeText_ = new Text(scene_, FontManager::get("Retron2000"),
                       {rect.x + rect.w / 2, rect.y + rect.h * 4 / 5},
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

void Battalion::loseHealth(int health) {
  if (Unit::getMaxHealth() <= health) {
    battalionSize_ -= health / Unit::getMaxHealth();
    if (battalionSize_ < 0) battalionSize_ = 0;
  }
  Unit::loseHealth(health);
  sizeText_->setText(sizeToString());
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

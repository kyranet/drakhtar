// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Battalion.h"
#include "Box.h"
#include "Managers/FontManager.h"
#include "Managers/GameManager.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"
#include "Text.h"

Battalion::Battalion(Scene *scene, Texture *texture, Box *box, const int attack,
                     const int defense, const int health, const int speed,
                     const int attackRange, const int moveRange,
                     const int prize, const std::string type,
                     const int battalionSize)
    : Unit(scene, texture, box, attack, defense, health, speed, attackRange,
           moveRange, prize * battalionSize, type),
      battalionSize_(battalionSize) {
  health_ = Unit::getMaxHealth() * battalionSize_;

  const SDL_Color textColor = {255, 255, 255, 255};

  healthText_->setText(healthToString());

  const auto rect = box_->getRect();

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

void Battalion::setBattalionSize(const int battalionSize) {
  battalionSize_ = battalionSize;
  sizeText_->setText(sizeToString());
}

int Battalion::getAttack() const { return Unit::getAttack() * battalionSize_; }

int Battalion::getMaxHealth() const {
  return Unit::getMaxHealth() * battalionSize_;
}

int Battalion::loseHealth(const int enemyAttack) {
  const auto health = Unit::loseHealth(enemyAttack);
  if (Unit::getMaxHealth() <= health) {
    battalionSize_ -= health / Unit::getMaxHealth();
    if (this->getTeam()->getColor() == Color::BLUE)
      (*GameManager::getInstance()->getArmy())[this->getType()] =
          battalionSize_;
    if (battalionSize_ < 0) battalionSize_ = 0;
    sizeText_->setText(sizeToString());
  }
  return health;
}

void Battalion::moveToBox(Box *box) {
  Unit::moveToBox(box);

  const auto rect = box_->getRect();

  sizeText_->setPosition(
      Vector2D<int>(rect.x + rect.w / 2, rect.y + rect.h * 4 / 5));
}

void Battalion::render() const {
  Unit::render();
  sizeText_->render();
}

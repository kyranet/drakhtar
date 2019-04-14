// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Battalion.h"
#include "Box.h"
#include "Managers/FontManager.h"
#include "Managers/GameManager.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"
#include "Text.h"
#include "HealthBar.h"

Battalion::Battalion(Scene *scene, Texture *texture, Box *box,
                     const UnitStats stats, const std::string type,
                     const int battalionSize)
    : Unit(scene, texture, box, stats, type), battalionSize_(battalionSize) {
  stats_.health = baseStats_.health * battalionSize_;

  const SDL_Color textColor = {255, 255, 255, 0};

  healthText_->setText(healthToString());

  const auto rect = box_->getRect();

  sizeText_ = new Text(scene, FontManager::get("UnitFont"),
                       {rect.x + rect.h/5, rect.y - rect.h/3},
                       textColor, sizeToString(), rect.w * 2);

  sizeText_->setColor(textColor);

  healthBar_->setMaxHP(baseStats_.health * battalionSize);
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

int Battalion::getAttack() const { return stats_.attack * battalionSize_; }

int Battalion::getDefense() const {
  return Unit::getDefense() * battalionSize_;
}

int Battalion::getMaxHealth() const {
  return baseStats_.health * battalionSize_;
}

int Battalion::loseHealth(const int enemyAttack) {
  const auto health = Unit::loseHealth(enemyAttack);
  if (baseStats_.health <= health) {
    battalionSize_ -= health / baseStats_.health;
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
      Vector2D<int>(rect.x + rect.h / 5, rect.y - rect.h / 3));
}

void Battalion::render() const {
  Unit::render();
  sizeText_->render();
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Battalion.h"
#include <algorithm>
#include "Box.h"
#include "HealthBar.h"
#include "Managers/FontManager.h"
#include "Managers/GameManager.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"
#include "Structures/Texture.h"
#include "Text.h"

Battalion::Battalion(Scene* scene, Texture* texture, Box* box,
                     const UnitStats stats, const std::string type,
                     const int battalionSize)
    : Unit(scene, texture, box, stats, type), battalionSize_(battalionSize) {
  stats_.maxHealth = baseStats_.maxHealth * battalionSize_;
  stats_.defense = baseStats_.defense;
  stats_.attack = baseStats_.attack * battalionSize_;
  stats_.prize = baseStats_.prize * battalionSize_;
  health_ = stats_.maxHealth;
  minDamage_ = battalionSize_;

  const SDL_Color textColor = {255, 255, 255, 0};
  const SDL_Color sizeColor = {0, 0, 255, 0};

  healthText_->setText(healthToString());

  const auto rect = box_->getRect();

  sizeText_ = new Text(scene, FontManager::get("TutorialFont"),
                       {rect.x + rect.h / 6, rect.y - rect.h / 3}, textColor,
                       sizeToString(), rect.w * 2);

  addChild(sizeText_);

  healthText_->setColor(textColor);

  sizeText_->setColor(sizeColor);

  healthBar_->setMaxHP(baseStats_.maxHealth * battalionSize);
}

Battalion::~Battalion() = default;

std::string Battalion::sizeToString() const {
  return std::to_string(battalionSize_);
}

void Battalion::setBattalionSize(const int battalionSize) {
  battalionSize_ = battalionSize;
  sizeText_->setText(sizeToString());
}

int Battalion::getAttack() const { return stats_.attack * battalionSize_; }

int Battalion::getDefense() const { return stats_.defense; }

int Battalion::getMaxHealth() const {
  return baseStats_.maxHealth * battalionSize_;
}

void Battalion::setAttack(const int attack) {
  stats_.attack = attack * battalionSize_;
}

int Battalion::loseHealth(const int enemyAttack, int minDamage) {
  const auto health = Unit::loseHealth(enemyAttack, minDamage);
  if (baseStats_.maxHealth * (battalionSize_ - 1) >= health_) {
    battalionSize_ -= std::max(health / baseStats_.maxHealth, 1);
    stats_.attack = baseStats_.attack * battalionSize_;
    if (battalionSize_ < 0) battalionSize_ = 0;
    minDamage_ = battalionSize_;
    sizeText_->setText(sizeToString());
    const SDL_Color sizeColor = {0, 0, 255, 0};
    sizeText_->setColor(sizeColor);
  }
  return health;
}

void Battalion::moveToBox(Box* box) {
  Unit::moveToBox(box);

  const auto rect = box_->getRect();
  sizeText_->setPosition(
      Vector2D<int>(rect.x + rect.h / 6, rect.y - rect.h / 3));
}

void Battalion::render() const {
  if (battalionSize_ > 3) {
    auto aux = getRect();
    aux.x += getTexture()->getFlip() == SDL_FLIP_HORIZONTAL ? -size_.getX() / 4
                                                            : size_.getX() / 4;
    aux.y -= size_.getY() / 5;
    texture_->renderFrame(aux, texture_->getAnimation()[texture_->getFrame()]);
  }
  Unit::render();
  if (battalionSize_ > 7) {
    auto aux = getRect();
    aux.x += getTexture()->getFlip() == SDL_FLIP_HORIZONTAL ? -size_.getX() / 4
                                                            : size_.getX() / 4;
    aux.y += size_.getY() / 5;
    texture_->renderFrame(aux, texture_->getAnimation()[texture_->getFrame()]);
  }
}

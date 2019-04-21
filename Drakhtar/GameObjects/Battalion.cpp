// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Battalion.h"

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
  stats_.health = baseStats_.health * battalionSize_;
  stats_.attack = baseStats_.attack * battalionSize_;
  stats_.prize = baseStats_.prize * battalionSize_;

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

  healthBar_->setMaxHP(baseStats_.health * battalionSize);

  centerLoneUnit();
}

Battalion::~Battalion() {}

std::string Battalion::sizeToString() const {
  return std::to_string(battalionSize_);
}

void Battalion::setBattalionSize(const int battalionSize) {
  battalionSize_ = battalionSize;
  sizeText_->setText(sizeToString());
}

int Battalion::getAttack() const { return stats_.attack * battalionSize_; }

int Battalion::getDefense() const { return Unit::getDefense(); }

int Battalion::getMaxHealth() const {
  return baseStats_.health * battalionSize_;
}

int Battalion::loseHealth(const int enemyAttack) {
  const auto health = Unit::loseHealth(enemyAttack);
  if (baseStats_.health <= health) {
    battalionSize_ -= health / baseStats_.health;
    stats_.attack = baseStats_.attack * battalionSize_;
    if (battalionSize_ < 0) battalionSize_ = 0;
    sizeText_->setText(sizeToString());
    const SDL_Color sizeColor = {0, 0, 255, 0};
    sizeText_->setColor(sizeColor);
    centerLoneUnit();
  }
  return health;
}

void Battalion::moveToBox(Box* box) {
  Unit::moveToBox(box);

  const auto rect = box_->getRect();

  sizeText_->setPosition(
      Vector2D<int>(rect.x + rect.h / 6, rect.y - rect.h / 3));

  centerLoneUnit();
}

void Battalion::render() const {
  SDL_Rect aux = getRect();
  if (battalionSize_ > 3) {
    aux.x -= box_->getRect().w / 2;
    aux.y -= box_->getRect().h / 3;
    texture_->renderFrame(aux, texture_->getAnimation()[texture_->getFrame()]);
  }
  Unit::render();
  if (battalionSize_ > 7) {
    aux.y += box_->getRect().h / 2;
    texture_->renderFrame(aux, texture_->getAnimation()[texture_->getFrame()]);
  }
}

void Battalion::centerLoneUnit() {
  if (battalionSize_ < 4) {
    setPosition(Vector2D<int>(box_->getRect().x + box_->getRect().w / 2,
                              box_->getRect().y + box_->getRect().h / 2));
  }
}

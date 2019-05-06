// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Battalion.h"

#include <algorithm>

#include "Box.h"
#include "HealthBar.h"
#include "Managers/FontManager.h"
#include "Managers/GameManager.h"
#include "../Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Structures/Game.h"
#include "Structures/Team.h"
#include "Structures/Texture.h"
#include "Text.h"

Battalion::Battalion(Scene* scene, Texture* texture, Box* box,
                     const UnitStats stats, const std::string& type,
                     const int battalionSize)
    : Unit(scene, texture, box, stats, type), battalionSize_(battalionSize) {
  stats_.maxHealth = baseStats_.maxHealth * battalionSize_;
  stats_.defense = baseStats_.defense;
  stats_.attack = baseStats_.attack * battalionSize_;
  stats_.prize = baseStats_.prize * battalionSize_;
  health_ = stats_.maxHealth;
  minDamage_ = battalionSize_;
}

void Battalion::setHealthBar() {
  Unit::setHealthBar();
  healthBar_->setMaxHP(baseStats_.maxHealth * battalionSize_);
  const SDL_Color textColor = {255, 255, 255, 0};
  const SDL_Color sizeColor = {0, 0, 255, 0};

  healthText_->setText(healthToString());

  const auto rect = box_->getRect();

  unitBattalionCircle_ =
      new GameObject(scene_, TextureManager::get("UI-BattalionCircle"),
                     {rect.x, rect.y - rect.h / 3}, {rect.w/3, rect.h/3});

  addChild(unitBattalionCircle_);

  sizeText_ = new Text(scene_, FontManager::get("TutorialFont"),
                       {rect.x, rect.y - rect.h / 3}, textColor,
                       sizeToString(), rect.w * 2);

  addChild(sizeText_);

  healthText_->setColor(textColor);

  sizeText_->setColor(textColor);
}

Battalion::~Battalion() = default;

std::string Battalion::sizeToString() const {
  return std::to_string(battalionSize_);
}

void Battalion::setBattalionSize(const int battalionSize) {
  battalionSize_ = battalionSize;
  health_ = baseStats_.maxHealth * battalionSize_;
  healthText_->setText(healthToString());
  healthText_->setColor({255, 255, 255, 0});
  sizeText_->setText(sizeToString());
  sizeText_->setColor({0, 0, 255, 0});
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
    int lostUnits = 1;
    while (baseStats_.maxHealth * (battalionSize_ - lostUnits - 1) >= health_)
      lostUnits++;
    battalionSize_ -= lostUnits;
    if (this->getTeam()->getColor() == Color::RED)
      reinterpret_cast<GameScene*>(Game::getSceneMachine()->getCurrentScene())
          ->addPrize(lostUnits * baseStats_.prize);

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
      Vector2D<int>(rect.x, rect.y - rect.h / 3));

  unitBattalionCircle_->setPosition(
      Vector2D<int>(rect.x, rect.y - rect.h / 3));
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

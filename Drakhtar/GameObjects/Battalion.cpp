// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Battalion.h"

#include <algorithm>

#include "../Managers/TextureManager.h"
#include "Box.h"
#include "HealthBar.h"
#include "Managers/FontManager.h"
#include "Managers/GameManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Structures/Game.h"
#include "Structures/Team.h"
#include "Structures/Texture.h"
#include "Text.h"

Battalion::Battalion(Scene* scene, Texture* texture, Box* box,
                     const UnitStats stats, const std::string& type,
                     const byte battalionSize)
    : Unit(scene, texture, box, stats, type), battalionSize_(battalionSize) {}

void Battalion::setHealthBar() {
  Unit::setHealthBar();
  healthBar_->setMaxHP(baseStats_.maxHealth * battalionSize_);
  const SDL_Color textColor = {255, 255, 255, 0};

  healthText_->setText(healthToString());

  const auto rect = box_->getRect();

  unitBattalionCircle_ =
      new GameObject(scene_, TextureManager::get("UI-BattalionCircle2"),
                     {rect.x, static_cast<int>(rect.y + rect.h / 1.31)},
                     {rect.w / 3, rect.h / 3});

  addChild(unitBattalionCircle_);

  sizeText_ = new Text(scene_, FontManager::get("TutorialFont"),
                       {rect.x, static_cast<int>(rect.y + rect.h / 1.31)},
                       textColor, sizeToString(), rect.w * 2);

  addChild(sizeText_);

  healthText_->setColor(textColor);

  sizeText_->setColor(textColor);
}

Battalion::~Battalion() = default;

std::string Battalion::sizeToString() const {
  return std::to_string(battalionSize_);
}

void Battalion::setBattalionSize(const byte battalionSize) {
  battalionSize_ = battalionSize;
  healthText_->setText(healthToString());
  healthText_->setColor({255, 255, 255, 0});
  sizeText_->setText(sizeToString());
  sizeText_->setColor({0, 0, 255, 0});
}

void Battalion::moveToBox(Box* box) {
  Unit::moveToBox(box);

  const auto rect = box_->getRect();
  sizeText_->setPosition(
      Vector2D<int>(rect.x, static_cast<int>(rect.y + rect.h / 1.31)));

  unitBattalionCircle_->setPosition(
      Vector2D<int>(rect.x, static_cast<int>(rect.y + rect.h / 1.31)));
}

void Battalion::render() const {
  if (battalionSize_ > 3) {
    auto aux = getRect();
    aux.x += getTexture()->getFlip() == SDL_FLIP_HORIZONTAL
                 ? -size_.getX() / 4
                 : size_.getX() / 4;
    aux.y -= size_.getY() / 5;
    texture_->renderFrame(aux, texture_->getAnimation()[texture_->getFrame()]);
  }
  if (battalionSize_ > 7) {
    auto aux = getRect();
    texture_->renderFrame(aux, texture_->getAnimation()[texture_->getFrame()]);
  }
  auto aux = getRect();
  aux.x += getTexture()->getFlip() == SDL_FLIP_HORIZONTAL
               ? -size_.getX() / 4
               : size_.getX() / 4;
  aux.y += size_.getY() / 5;
  Unit::render(aux);
}

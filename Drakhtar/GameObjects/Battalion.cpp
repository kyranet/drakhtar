// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Battalion.h"

#include "Box.h"
#include "HealthBar.h"
#include "Managers/FontManager.h"
#include "Managers/GameManager.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"
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

  healthText_->setColor(textColor);

  sizeText_->setColor(sizeColor);

  healthBar_->setMaxHP(baseStats_.health * battalionSize);

  setSize(Vector2D<int>(static_cast<int>(box->getRect().w * 1.25),
                        static_cast<int>(box->getRect().h * 2)));

  auxiliaryUnit1_ =
      new GameObject(scene, texture,
                     Vector2D<int>(box->getRect().x + box->getRect().w / 1.8,
                                   box->getRect().y + box->getRect().h / 2),
                     Vector2D<int>(static_cast<int>(box->getRect().w * 2),
                                   static_cast<int>(box->getRect().h * 2)));

  auxiliaryUnit2_ =
      new GameObject(scene, texture,
                     Vector2D<int>(box->getRect().x - box->getRect().w / 4,
                                   box->getRect().y + box->getRect().h / 2),
                     Vector2D<int>(static_cast<int>(box->getRect().w * 2),
                                   static_cast<int>(box->getRect().h * 2)));
}

Battalion::~Battalion() {
  if (sizeText_ != nullptr) {
    delete sizeText_;
    sizeText_ = nullptr;
  }

  if (auxiliaryUnit1_ != nullptr) {
    delete auxiliaryUnit1_;
    auxiliaryUnit1_ = nullptr;
  }

  if (auxiliaryUnit2_ != nullptr) {
    delete auxiliaryUnit2_;
    auxiliaryUnit2_ = nullptr;
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
  return Unit::getDefense();
}

int Battalion::getMaxHealth() const {
  return baseStats_.health * battalionSize_;
}

int Battalion::loseHealth(const int enemyAttack) {
  const auto health = Unit::loseHealth(enemyAttack);
  if (baseStats_.health <= health) {
    battalionSize_ -= health / baseStats_.health;
    stats_.attack = baseStats_.attack * battalionSize_;
    if (this->getTeam()->getColor() == Color::BLUE)
      (*GameManager::getInstance()->getArmy())[this->getType()] =
          battalionSize_;
    if (battalionSize_ < 0) battalionSize_ = 0;
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

  auxiliaryUnit1_->setPosition(
      Vector2D<int>(box->getRect().x + box->getRect().w / 1.8,
                    box->getRect().y + box->getRect().h / 2));

  auxiliaryUnit2_->setPosition(
      Vector2D<int>(box->getRect().x - box->getRect().w / 1.8,
                    box->getRect().y + box->getRect().h / 2));
}

void Battalion::render() const {
  Unit::render();
  sizeText_->render();
  auxiliaryUnit1_->render();
  auxiliaryUnit2_->render();
}

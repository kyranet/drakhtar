// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Unit.h"
#include <algorithm>
#include "../Managers/FontManager.h"
#include "../Structures/Team.h"
#include "../Utils/Vector2D.h"
#include "Board.h"
#include "Box.h"
#include "HealthBar.h"
#include "Managers/FontManager.h"
#include "Scenes/GameScene.h"
#include "Structures/Team.h"
#include "Text.h"

Unit::Unit(Scene* scene, Texture* texture, Box* box, UnitStats stats,
           const std::string& type)
    : GameObject(scene, texture,
                 Vector2D<int>(box->getRect().x + box->getRect().w / 2,
                               box->getRect().y + box->getRect().h / 2),
                 Vector2D<int>(static_cast<int>(box->getRect().w * 1.25),
                               static_cast<int>(box->getRect().h * 1.25))),
      boxPosition_(box->getPosition()),
      type_(type),
      box_(box),
      health_(stats.health),
      baseStats_(stats),
      stats_(stats) {
  // Units must be ignored in the mouse raycasts.
  setTransparent(true);
  box->setContent(this);
  const SDL_Color textColor = {255, 255, 255, 0};
  const auto rect = box_->getRect();

  healthText_ =
      new Text(scene, FontManager::get("UnitFont"),
               {rect.x + rect.w / 2 + rect.w / 14, rect.y - rect.h / 3},
               textColor, healthToString(), rect.w * 2);

  healthBar_ = new HealthBar(
      scene, Vector2D<int>(rect.x + rect.w / 2, rect.y - rect.h / 3),
      baseStats_.health);

  healthText_->setColor(textColor);

  healthText_->setTransparent(true);
  healthBar_->setTransparent(true);

  addChild(healthBar_);
  addChild(healthText_);
}

Unit::~Unit() = default;

void Unit::moveToBox(Box* newBox) {
  box_->setContent(nullptr);
  setPosition(Vector2D<int>(newBox->getRect().x + newBox->getRect().w / 2,
                            newBox->getRect().y + newBox->getRect().h / 2));
  box_ = newBox;
  newBox->setContent(this);
  const auto rect = box_->getRect();
  healthText_->setPosition(
      {rect.x + rect.w / 2 + rect.w / 14, rect.y - rect.h / 3});
  healthBar_->moveBar(Vector2D<int>(rect.x + rect.w / 2, rect.y - rect.h / 3));
  setMoved(true);
  setMoving(false);
}

int Unit::loseHealth(int enemyAttack) {
  enemyAttack = enemyAttack * (1 - static_cast<float>(getDefense()) / 100);

  health_ = std::max(health_ - enemyAttack, 0);
  stats_.health = std::max(stats_.health - enemyAttack, 0);

  healthText_->setText(healthToString());
  const SDL_Color textColor = {255, 255, 255, 0};
  healthText_->setColor(textColor);
  healthBar_->takeDamage(getStats().health);

  return enemyAttack;
}

void Unit::update() { healthBar_->update(); }

void Unit::onSelect() { setMoving(true); }

void Unit::onDeselect() { setMoving(false); }

void Unit::attack(Unit* enemy, const bool counter) {
  enemy->loseHealth(getStats().attack);

  const auto scene = reinterpret_cast<GameScene*>(getScene());
  // If the attack is not a counter and the enemy is
  // alive and within attack range, counter-attack
  if (!counter && enemy->getStats().health > 0 &&
      scene->getBoard()->isInRange(box_, enemy->getBox(),
                                   enemy->getStats().attackRange)) {
    enemy->attack(this, true);
  }
}

void Unit::kill() { getTeam()->removeUnit(this); }

std::string Unit::healthToString() const {
  return std::to_string(getStats().health) + " HP";
}

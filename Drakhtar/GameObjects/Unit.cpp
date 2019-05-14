// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Unit.h"
#include <algorithm>
#include "Board.h"
#include "Box.h"
#include "EventListeners/SkillButtonListener.h"
#include "HealthBar.h"
#include "Managers/FontManager.h"
#include "Managers/State.h"
#include "Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Structures/Team.h"
#include "Text.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"

Unit::Unit(Scene* scene, Texture* texture, Box* box, UnitStats stats,
           const std::string& type)
    : GameObject(scene, texture,
                 {box->getRect().x + box->getRect().w / 2,
                  box->getRect().y + box->getRect().h / 2},
                 {static_cast<int>(WIN_HEIGHT / 5.625f),
                  static_cast<int>(WIN_HEIGHT / 5.625f)}),
      type_(type),
      box_(box),
      baseStats_(stats) {
  // Units must be ignored in the mouse raycasts.
  setTransparent(true);
  box->setContent(this);
}

Unit::~Unit() = default;

void Unit::setHealthBar() {
  const auto rect = box_->getRect();
  if (getTeam()->getColor() == Color::RED) {
    healthBar_ =
        new HealthBar(scene_,
                      Vector2D<int>(rect.x + rect.w / 2,
                                    static_cast<int>(rect.y + rect.h / 1.2)),
                      baseStats_.maxHealth, Color::RED);
  } else {
    healthBar_ =
        new HealthBar(scene_,
                      Vector2D<int>(rect.x + rect.w / 2,
                                    static_cast<int>(rect.y + rect.h / 1.2)),
                      baseStats_.maxHealth, Color::BLUE);
  }
  healthBar_->setTransparent(true);
  addChild(healthBar_);

  const SDL_Color textColor = {255, 255, 255, 0};

  healthText_ = new Text(scene_, FontManager::get("UnitFont"),
                         {rect.x + rect.w / 2 + rect.w / 14,
                          static_cast<int>(rect.y + rect.h / 1.2)},
                         textColor, healthToString(), rect.w * 2);

  healthText_->setColor(textColor);

  healthText_->setTransparent(true);

  addChild(healthText_);
}

void Unit::moveToBox(Box* newBox) {
  box_->setContent(nullptr);
  setPosition(Vector2D<int>(newBox->getRect().x + newBox->getRect().w / 2,
                            newBox->getRect().y + newBox->getRect().h / 2));
  box_ = newBox;
  newBox->setContent(this);
  const auto rect = box_->getRect();
  healthText_->setPosition({rect.x + rect.w / 2 + rect.w / 14,
                            static_cast<int>(rect.y + rect.h / 1.2)});
  healthBar_->moveBar(Vector2D<int>(rect.x + rect.w / 2,
                                    static_cast<int>(rect.y + rect.h / 1.2)));
}

int Unit::loseHealth(int enemyAttack, int) {
  // enemyAttack = static_cast<int>(enemyAttack * (1.0 - stats_.defense / 100.0));
  // enemyAttack = std::min(std::max(enemyAttack, minDamage), stats_.maxHealth);

  // health_ = std::max(health_ - enemyAttack, 0);

  healthText_->setText(healthToString());
  const SDL_Color textColor = {255, 255, 255, 0};
  healthText_->setColor(textColor);
  // healthBar_->takeDamage(health_);

  return enemyAttack;
}

void Unit::update() { healthBar_->update(); }

void Unit::onSelect() {
  setHasCounterAttacked(false);
}

void Unit::onDeselect() { /* setMoving(false); */ }

void Unit::setBuffed(bool buffed) { healthBar_->setStatUpRenderizable(buffed); }

void Unit::setDebuffed(bool debuffed) {
  healthBar_->setStatDownRenderizable(debuffed);
}

void Unit::attack(Unit* enemy, const bool) {
  // enemy->loseHealth(getStats().attack, minDamage_);

  const auto scene = reinterpret_cast<GameScene*>(getScene());
  const auto state = scene->getState();

  // If the target is an archer and is in range 1, it can never counter-attack
  if (enemy->getType() == "Archer" &&
      state->isInRange(box_->getIndex(), enemy->getBox()->getIndex(), 1)) {
    return;
  }

  // If the attack allows a counter and the enemy is
  // alive and within attack range, counter-attack
  // if (allowsCounter && enemy->getHealth() > 0 &&
  //     state->isInRange(box_->getIndex(), enemy->getBox()->getIndex(),
  //                      enemy->getStats().attackRange) &&
  //     !enemy->getHasCounterAttacked()) {
  //   enemy->attack(this, false);
  //   enemy->setHasCounterAttacked(true);
  // }
}

void Unit::kill() {
  getTeam()->removeUnit(this);

  const auto scene = reinterpret_cast<GameScene*>(getScene());
  scene->getState()->removeAt(getBox()->getIndex());
  scene->removeGameObject(this);
}

std::string Unit::healthToString() const {
  const auto scene = reinterpret_cast<GameScene*>(getScene());
  const auto state = scene->getState();
  const auto stats = state->getAt(getBox()->getIndex());
  return std::to_string(stats.health_) + " HP";
}

bool Unit::isCommander() const { return isCommander_; }

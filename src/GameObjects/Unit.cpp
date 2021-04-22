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
#include "Structures/Game.h"
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
}

Unit::~Unit() = default;

void Unit::awake() {
  GameObject::awake();
  setHealthBar();
}

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
  setPosition(Vector2D<int>(newBox->getRect().x + newBox->getRect().w / 2,
                            newBox->getRect().y + newBox->getRect().h / 2));
  box_ = newBox;
  const auto rect = box_->getRect();
  healthText_->setPosition({rect.x + rect.w / 2 + rect.w / 14,
                            static_cast<int>(rect.y + rect.h / 1.2)});
  healthBar_->moveBar(Vector2D<int>(rect.x + rect.w / 2,
                                    static_cast<int>(rect.y + rect.h / 1.2)));

  reinterpret_cast<GameScene*>(Game::getSceneMachine()->getCurrentScene())
      ->updateRenderOrder(this);
}

void Unit::update() {
  healthBar_->update();
  healthBar_->setStatUpRenderizable(isBuffed());
  healthBar_->setStatDownRenderizable(isNerfed());
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
  const auto stats = state->getModifiedAt(getBox()->getIndex());
  return std::to_string(stats.health_) + " HP";
}

bool Unit::isCommander() const { return isCommander_; }

bool Unit::isBuffed() const {
  const auto scene = reinterpret_cast<GameScene*>(getScene());
  const auto state = scene->getState();
  const auto stats = state->getAt(getBox()->getIndex());
  for (const auto& modifier : stats.modifiers_) {
    if (modifier.buff_) return true;
  }
  return false;
}

bool Unit::isNerfed() const {
  const auto scene = reinterpret_cast<GameScene*>(getScene());
  const auto state = scene->getState();
  const auto stats = state->getAt(getBox()->getIndex());
  for (const auto& modifier : stats.modifiers_) {
    if (modifier.nerf_) return true;
  }
  return false;
}

bool Unit::operator<(const Unit& unit) const {
  auto boxAIndex = getBox()->getIndex();
  auto boxBIndex = unit.getBox()->getIndex();
  if (boxAIndex.getY() < boxBIndex.getY())
    return true;
  else if (boxAIndex.getY() == boxBIndex.getY() &&
           boxAIndex.getX() < boxBIndex.getX())
    return true;
  else
    return false;
}

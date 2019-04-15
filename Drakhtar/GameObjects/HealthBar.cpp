// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "HealthBar.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Utils/Constants.h"

HealthBar::HealthBar(Scene *scene, Vector2D<int> pos, int maxHP)
    : GameObject(scene, TextureManager::get("UI-healthBar_background"), pos,
                 Vector2D<int>(WIN_WIDTH / 20, WIN_HEIGHT / 60)) {
  lifeBar = new GameObject(scene, TextureManager::get("UI-healthBar_life"), pos,
                           Vector2D<int>(getRect().w, getRect().h));
  damageBar = new GameObject(scene, TextureManager::get("UI-healthBar_damage"),
                             pos, Vector2D<int>(getRect().w, getRect().h));
  damageBar->setActive(false);

  originalWidth = lifeBar->getRect().w;
  maxHealth = maxHP;
  currentHealth = maxHealth;
}

HealthBar::~HealthBar() {
  delete lifeBar;
  delete damageBar;
}

void HealthBar::render() const {
  GameObject::render();
  lifeBar->render();

  if (damageBar->getActive())
    damageBar->render();
}

void HealthBar::update() {
  if (damageAnimationPlaying && damageBar->getRect().w > 0) {
    if (damageBar->getRect().w > damageAnimationSpeed) {
      int oldX = damageBar->getRect().x;
      int oldY = damageBar->getRect().y;
      damageBar->setSize(
          Vector2D<int>(damageBar->getRect().w - damageAnimationSpeed,
                        damageBar->getRect().h));
      damageBar->setPosition(
          Vector2D<int>(oldX + (damageBar->getRect().w / 2),
                        oldY + (damageBar->getRect().h / 2)));
    } else {
      damageBar->setSize(Vector2D<int>(0, damageBar->getRect().h));
      damageBar->setActive(false);
      damageAnimationPlaying = false;
    }
  }
}

void HealthBar::takeDamage(int newHealth) {
  int damage = currentHealth - newHealth;

  currentHealth = newHealth;
  double lifeProportion = static_cast<double>(currentHealth) / maxHealth;
  int oldX = lifeBar->getRect().x;
  int oldY = lifeBar->getRect().y;
  lifeBar->setSize(
      Vector2D<int>(originalWidth * lifeProportion, lifeBar->getRect().h));
  lifeBar->setPosition(Vector2D<int>(oldX + (lifeBar->getRect().w / 2),
                                     oldY + (lifeBar->getRect().h / 2)));

  double damageProportion = static_cast<double>(damage) / maxHealth;
  damageBar->setSize(
      Vector2D<int>(originalWidth * damageProportion, damageBar->getRect().h));
  damageBar->setPosition(
      Vector2D<int>(lifeBar->getRect().x + (lifeBar->getRect().w) +
                        (damageBar->getRect().w / 2),
                    damageBar->getRect().y + (lifeBar->getRect().h / 2)));
  damageBar->setActive(true);
  damageAnimationPlaying = true;
}

void HealthBar::moveBar(Vector2D<int> pos) {
  setPosition(pos);
  lifeBar->setPosition(pos);
  damageBar->setPosition(pos);
}

void HealthBar::setMaxHP(int hp) {
  maxHealth = hp;
  currentHealth = maxHealth;
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"
#include "SDL.h"

class Scene;

class HealthBar : public GameObject {
 private:
  GameObject *lifeBar = nullptr;
  GameObject *damageBar = nullptr;

  int maxHealth;
  int currentHealth;

  double damageAnimationSpeed = 0.5;
  bool damageAnimationPlaying = false;

  int originalWidth;

 public:
  HealthBar(Scene *scene, Vector2D<int> pos, int maxHP);
  virtual ~HealthBar();
  virtual void render() const;
  virtual void update();
  void takeDamage(int newHealth);
  void moveBar(Vector2D<int> pos);
  void setMaxHP(int hp);
};

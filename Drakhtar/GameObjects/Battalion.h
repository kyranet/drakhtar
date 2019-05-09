// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>

#include "Unit.h"

class Scene;
class Texture;
class Text;
class HealthBar;

class Battalion final : public Unit {
  int battalionSize_;
  Text* sizeText_ = nullptr;
  GameObject* unitBattalionCircle_ = nullptr;

  Vector2D<int> offset;

  std::string sizeToString() const;

 public:
  Battalion(Scene* scene, Texture* texture, Box* box, const UnitStats stats,
            const std::string& type, int battalionSize);
  virtual ~Battalion();

  int getBattalionSize() const { return battalionSize_; }
  void setBattalionSize(int battalionSize);

  void setHealthBar() override;

  int getAttack() const;
  int getDefense() const override;
  int getMaxHealth() const;

  void setAttack(int attack) override;

  int loseHealth(int enemyAttack, int minDamage) override;

  void moveToBox(Box* box) override;
  void render() const override;
};

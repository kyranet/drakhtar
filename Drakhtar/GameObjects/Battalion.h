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

  std::string sizeToString() const;

 public:
  Battalion(Scene* scene, Texture* texture, Box* box, const UnitStats stats,
            std::string & type, int battalionSize);
  virtual ~Battalion();

  int getBattalionSize() const { return battalionSize_; }
  void setBattalionSize(int battalionSize);

  int getAttack() const;
  int getDefense() const override;
  int getMaxHealth() const;

  void setAttack(int attack) override;

  int loseHealth(int enemyAttack, int minDamage) override;

  void moveToBox(Box* box) override;
  void render() const override;
};

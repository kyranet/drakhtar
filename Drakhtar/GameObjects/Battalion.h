// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>
#include "Unit.h"

class Scene;
class Texture;
class Text;

class Battalion final : public Unit {
  int battalionSize_;
  Text* sizeText_ = nullptr;

  std::string sizeToString() const;

 public:
  Battalion(Scene* scene, Texture* texture, Box* box, int attack, int defense,
            int health, int speed, int attackRange, int moveRange, int prize,
            int battalionSize);
  virtual ~Battalion();

  int getBattalionSize() const { return battalionSize_; }
  void setBattalionSize(int battalionSize);

  int getAttack() const override;
  int getMaxHealth() const override;

  int loseHealth(int enemyAttack) override;

  void moveToBox(Box* box) override;
  void render() const override;
};

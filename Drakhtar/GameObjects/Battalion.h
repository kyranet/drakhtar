// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>

#include "Unit.h"

class Scene;
class Texture;
class Text;
class HealthBar;

class Battalion final : public Unit {
  byte battalionSize_;
  Text* sizeText_ = nullptr;
  GameObject* unitBattalionCircle_ = nullptr;

  std::string sizeToString() const;

 public:
  Battalion(Scene* scene, Texture* texture, Box* box, const UnitStats stats,
            const std::string& type, byte battalionSize);
  virtual ~Battalion();

  byte getBattalionSize() const { return battalionSize_; }
  void setBattalionSize(byte battalionSize);

  void setHealthBar() override;

  void moveToBox(Box* box) override;
  void render() const override;
};

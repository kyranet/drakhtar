// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>

#include "Unit.h"

class Scene;
class Texture;
class Text;
class HealthBar;

class Battalion final : public Unit {
  uint16_t battalionSize_;
  Text* sizeText_ = nullptr;
  GameObject* unitBattalionCircle_ = nullptr;

  std::string sizeToString() const;

 public:
  Battalion(Scene* scene, Texture* texture, Box* box, const UnitStats stats,
            const std::string& type, uint16_t battalionSize);
  virtual ~Battalion();

  uint16_t getBattalionSize() const { return battalionSize_; }
  void setBattalionSize(uint16_t battalionSize);

  void setHealthBar() override;

  void moveToBox(Box* box) override;
  void render() const override;
};

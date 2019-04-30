// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "EventListeners/StoreListener.h"
#include "GameObject.h"

class Scene;
class Text;
class Unit;

class UnitDescriptionBox final : public GameObject {
  Unit* unit_;
  Text* skillTextSprite_;

 public:
  UnitDescriptionBox(Scene* scene, Unit* unit);
  ~UnitDescriptionBox() = default;

  void render() const override;
  std::string fillText() const;
  void updateText() const;
};

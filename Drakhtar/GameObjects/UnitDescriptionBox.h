// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"

class Scene;
class Text;
class Unit;
class StatBoxListener;
class Board;

class UnitDescriptionBox final : public GameObject {
  Text* unitStatsText_;
  Text* unitDamageText_;
  StatBoxListener* listener_;

 public:
  UnitDescriptionBox(Scene* scene, Board* board);
  ~UnitDescriptionBox() = default;

  void render() const override;
  //std::string fillText() const;
  void updateText(Unit* unit) const;

  void show();
  void hide();
};

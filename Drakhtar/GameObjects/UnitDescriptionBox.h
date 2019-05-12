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
  Board* board_;
  bool showDamage_;

 public:
  UnitDescriptionBox(Scene* scene, Board* board);
  ~UnitDescriptionBox() = default;

  void render() const override;
  void updateText(Unit* unit);
};

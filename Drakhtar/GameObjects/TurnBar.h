// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <list>
#include <vector>
#include "GameObject.h"
#include "SDL.h"

class Scene;
class Unit;

class TurnBar final : public GameObject {
  std::list<Unit *> unitTurnBar_;
  size_t visibleTurnBarSize_ = 9;
  std::vector<GameObject *> visibleUnits_;
  GameObject* selectedUnitSprite_ = nullptr;


 public:
  // constructor interlaces units from each team list into the turn bar (ally
  // -> enemy -> ally -> etc)
  TurnBar(Scene *scene, std::list<Unit *> allyList,
          std::list<Unit *> enemyList);
  virtual ~TurnBar();
  Unit *getFrontUnit() { return unitTurnBar_.front(); }
  void advanceTurn();
  void sort();
  void eraseUnit(Unit *unit);
  void render() const override;
  void handleEvents(SDL_Event event) override;
  void updateVisibleUnits();
  void decreaseVisibleUnitsSize();
};

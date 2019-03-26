// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <list>
#include <queue>
#include <vector>
#include "GameObject.h"
#include "SDL.h"

class Scene;
class Unit;

class TurnBar : public GameObject {
 private:
  std::list<Unit *> unitTurnBar;
  int visibleTurnBarSize = 9;
  std::vector<GameObject *> visibleUnits;
  GameObject* selectedUnitSprite = nullptr;


 public:
  // constructor intercalates units from each team list into the turn bar (ally
  // -> enemy -> ally -> etc)
  TurnBar(Scene *scene, std::list<Unit *> allyList,
          std::list<Unit *> enemyList);
  virtual ~TurnBar();
  Unit *getFrontUnit() { return unitTurnBar.front(); }
  void advanceTurn();
  void sort();
  void eraseUnit(Unit *unit);
  virtual void render() const;
  virtual void handleEvents(SDL_Event event);
  void updateVisibleUnits();
  void decreaseVisibleUnitsSize();
};

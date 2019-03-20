// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <list>
#include <queue>
#include <vector>
#include "TextureManager.h"
#include "Unit.h"

class TurnBar : public GameObject {
 private:
  list<Unit *> unitTurnBar;
  int visibleTurnBarSize = 9;
  vector<GameObject *> visibleUnits;

 public:
  TurnBar();
  // constructor intercalates units from each team list into the turn bar (ally
  // -> enemy -> ally -> etc)
  TurnBar(list<Unit *> allyList, list<Unit *> enemyList);
  virtual ~TurnBar();
  Unit *getFrontUnit() { return unitTurnBar.front(); }
  void advanceTurn();
  virtual void render() const;
  virtual void handleEvents(SDL_Event event);
  void updateVisibleUnits();
  void deleteUnit(Unit *unit);
};

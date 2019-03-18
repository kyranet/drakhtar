// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <queue>
#include <list>
#include <vector>
#include "Unit.h"
#include "TextureManager.h"

class TurnBar : public GameObject
{
 private:
    list<Unit *> unitTurnBar;
    int visibleTurnBarSize = 9;
    vector<GameObject *> visibleUnits;

 public:
    // constructor intercalates units from each team list into the turn bar (ally -> enemy -> ally -> etc)
    TurnBar(list<Unit *> allyList, list<Unit *> enemyList);
    virtual ~TurnBar();
    Unit *getFrontUnit() { return unitTurnBar.front(); }
    void advanceTurn();
	void sort();
    virtual void render() const;
    virtual void handleEvents(SDL_Event event);
    void updateVisibleUnits();
};

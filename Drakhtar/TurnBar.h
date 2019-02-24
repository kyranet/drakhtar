#pragma once

#include <queue>
#include <list>
#include "Unit.h"

class TurnBar
{
private:
	queue<Unit*> unitTurnBar;
public:
	// constructor intercalates units from each team list into the turn bar (ally -> enemy -> ally -> etc)
	TurnBar(list<Unit*> allyList, list<Unit*> enemyList);
	virtual ~TurnBar();
	Unit* getFrontUnit() { return unitTurnBar.front(); }
	void advanceTurn();
};


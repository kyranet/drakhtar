#pragma once

#include <queue>
#include "Unit.h"

class TurnBar
{
private:
	queue<Unit*> unitTurnBar;
public:
	TurnBar();
	virtual ~TurnBar();
	Unit* getFrontUnit() { return unitTurnBar.front(); }
	void advanceTurn();
};


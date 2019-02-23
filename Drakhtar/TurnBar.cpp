#include "TurnBar.h"



TurnBar::TurnBar()
{
}


TurnBar::~TurnBar()
{
}

// takes out the unit in the front of the queue and puts it in the back
void TurnBar::advanceTurn()
{
	Unit* frontUnit = unitTurnBar.front();
	unitTurnBar.pop();
	unitTurnBar.push(frontUnit);
}

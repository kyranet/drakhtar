#include "TurnBar.h"



TurnBar::TurnBar(list<Unit*> allyList, list<Unit*> enemyList): GameObject(nullptr, Vector2D<int>(0,0), Vector2D<int>(0, 0))
{
	auto allyIt = allyList.begin();
	auto enemyIt = enemyList.begin();
	int unitCount = 0;

	while (allyIt != allyList.end() && enemyIt != enemyList.end())
	{
		if (unitCount % 2 == 0 && allyIt != allyList.end())
		{
			unitTurnBar.push_back(*allyIt);
			allyIt++;
		}
		else if(enemyIt != enemyList.end())
		{
			unitTurnBar.push_back(*enemyIt);
			enemyIt++;
		}
		unitCount++;
	}
}


TurnBar::~TurnBar()
{
}

// takes out the unit in the front of the queue and puts it in the back
void TurnBar::advanceTurn()
{
	Unit* frontUnit = unitTurnBar.front();
	unitTurnBar.pop_front();
	unitTurnBar.push_back(frontUnit);
}

void TurnBar::render()
{
}

void TurnBar::handleEvents(SDL_Event event)
{
}

#include "TurnBar.h"



TurnBar::TurnBar() : GameObject(TextureManager::get("UI-turnBar"), Vector2D<int>(WIN_WIDTH - 215, WIN_HEIGHT - 30), Vector2D<int>(400, 50))
{
	// example for testing the turnBar
	visibleUnits.resize(visibleTurnBarSize);
	
	visibleUnits[0] = new GameObject(TextureManager::get("Portraits-Thassa"), Vector2D<int>(WIN_WIDTH - 432 + 1 * 44, WIN_HEIGHT - 30), Vector2D<int>(30, 30));
	visibleUnits[1] = new GameObject(TextureManager::get("Portraits-Archer"), Vector2D<int>(WIN_WIDTH - 432 + 2 * 44, WIN_HEIGHT - 30), Vector2D<int>(30, 30));
	visibleUnits[2] = new GameObject(TextureManager::get("Portraits-ArcherEnemy"), Vector2D<int>(WIN_WIDTH - 432 + 3 * 44, WIN_HEIGHT - 30), Vector2D<int>(30, 30));
	visibleUnits[3] = new GameObject(TextureManager::get("Portraits-Knight"), Vector2D<int>(WIN_WIDTH - 432 + 4 * 44, WIN_HEIGHT - 30), Vector2D<int>(30, 30));
	visibleUnits[4] = new GameObject(TextureManager::get("Portraits-KnightEnemy"), Vector2D<int>(WIN_WIDTH - 432 + 5 * 44, WIN_HEIGHT - 30), Vector2D<int>(30, 30));
	visibleUnits[5] = new GameObject(TextureManager::get("Portraits-Mage"), Vector2D<int>(WIN_WIDTH - 432 + 6 * 44, WIN_HEIGHT - 30), Vector2D<int>(30, 30));
	visibleUnits[6] = new GameObject(TextureManager::get("Portraits-MageEnemy"), Vector2D<int>(WIN_WIDTH - 432 + 7 * 44, WIN_HEIGHT - 30), Vector2D<int>(30, 30));
	visibleUnits[7] = new GameObject(TextureManager::get("Portraits-Narrator"), Vector2D<int>(WIN_WIDTH - 432 + 8 * 44, WIN_HEIGHT - 30), Vector2D<int>(30, 30));
	visibleUnits[8] = new GameObject(TextureManager::get("Portraits-SoldierEnemy"), Vector2D<int>(WIN_WIDTH - 432 + 9 * 44, WIN_HEIGHT - 30), Vector2D<int>(30, 30));
}

TurnBar::TurnBar(list<Unit*> allyList, list<Unit*> enemyList): GameObject(TextureManager::get("UI-turnBar"), Vector2D<int>(100,100), Vector2D<int>(100, 100))
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

	visibleUnits.resize(visibleTurnBarSize);
	auto listIt = unitTurnBar.begin();
	for(int i=0;i< visibleTurnBarSize;i++)
	{
		visibleUnits[i] = new GameObject((*listIt)->getTexture(), Vector2D<int>(WIN_WIDTH - 432 + (i + 1) * 44, WIN_HEIGHT - 30), Vector2D<int>(30, 30));
		listIt++;
	}
}


TurnBar::~TurnBar()
{
	for (auto unit : visibleUnits)
		delete unit;
}

// takes out the unit in the front of the queue and puts it in the back
void TurnBar::advanceTurn()
{
	Unit* frontUnit = unitTurnBar.front();
	unitTurnBar.pop_front();
	unitTurnBar.push_back(frontUnit);
}

void TurnBar::render() const
{
	GameObject::render();
	for (auto unit : visibleUnits)
		unit->render();
}

void TurnBar::handleEvents(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_t:
			advanceTurn();
			updateVisibleUnits();
			break;
		}
	}
}

void TurnBar::updateVisibleUnits()
{
	auto listIt = unitTurnBar.begin();
	for (int i = 0;i < visibleTurnBarSize;i++)
	{
		visibleUnits[i]->setTexture((*listIt)->getTexture());
		listIt++;
	}
}



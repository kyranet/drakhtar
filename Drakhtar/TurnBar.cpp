// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TurnBar.h"

TurnBar::TurnBar(list<Unit *> allyList, list<Unit *> enemyList)
    : GameObject(TextureManager::get("UI-turnBar"),
                 Vector2D<int>(WIN_WIDTH - 215, WIN_HEIGHT - 30),
                 Vector2D<int>(400, 50)) {
  auto allyIt = allyList.begin();
  auto enemyIt = enemyList.begin();
  int unitCount = 0;

  while (allyIt != allyList.end() || enemyIt != enemyList.end()) {
    if (unitCount % 2 == 0 && allyIt != allyList.end()) {
      unitTurnBar.push_back(*allyIt);
      allyIt++;
    } else if (enemyIt != enemyList.end()) {
      unitTurnBar.push_back(*enemyIt);
      enemyIt++;
    }
    unitCount++;
  }

  visibleUnits.resize(visibleTurnBarSize);
  auto listIt = unitTurnBar.begin();
  for (int i = 0; i < visibleTurnBarSize; i++) {
    visibleUnits[i] = new GameObject(
        (*listIt)->getTexture(),
        Vector2D<int>(WIN_WIDTH - 432 + (i + 1) * 44, WIN_HEIGHT - 30),
        Vector2D<int>(45, 45));
    listIt++;
  }
  // example for testing sort
  // auto e = allyList.begin();
  // unitTurnBar.push_back(*e);
  // unitTurnBar.push_back(*e);
  // unitTurnBar.push_back(*e);
  // unitTurnBar.push_back(*e);
  // unitTurnBar.push_back(*e);
  sort();
}

TurnBar::~TurnBar() {
  for (auto unit : visibleUnits) delete unit;
}

// takes out the unit in the front of the queue and puts it in the back
void TurnBar::advanceTurn() {
  Unit *frontUnit = unitTurnBar.front();
  unitTurnBar.pop_front();
  unitTurnBar.push_back(frontUnit);
  updateVisibleUnits();
}

void TurnBar::sort() {
  unitTurnBar.sort([](Unit *unit1, Unit *unit2) {
    return unit1->getSpeed() > unit2->getSpeed();
  });
  updateVisibleUnits();
}

void TurnBar::eraseUnit(Unit *unit) {
  bool deleted = false;
  auto it = unitTurnBar.begin();
  while (!deleted && it != unitTurnBar.end()) {
    if ((*it) == unit) {
      unitTurnBar.erase(it);
      deleted = true;

      if (visibleTurnBarSize > unitTurnBar.size()) decreaseVisibleUnitsSize();
    } else {
      it++;
    }
  }
  updateVisibleUnits();
}

void TurnBar::render() const {
  GameObject::render();
  for (auto unit : visibleUnits) unit->render();
}

void TurnBar::handleEvents(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_t:
            advanceTurn();
            break;
        }
    }
  }
}

void TurnBar::updateVisibleUnits() {
  auto listIt = unitTurnBar.begin();
  for (int i = 0; i < visibleTurnBarSize; i++) {
    visibleUnits[i]->setTexture((*listIt)->getTexture());
    listIt++;
  }
}

void TurnBar::decreaseVisibleUnitsSize() {
  visibleTurnBarSize--;
  delete visibleUnits[visibleTurnBarSize];
  visibleUnits.resize(visibleTurnBarSize);
}

void TurnBar::deleteUnit(Unit * unit) 
{
	auto it = unitTurnBar.begin();
	while (it != unitTurnBar.end())
	{
		if (*it == unit)
		{
			unitTurnBar.erase(it);
			break;
		}
		it++;
	}
}

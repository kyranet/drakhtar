// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TurnBar.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Utils/Constants.h"
#include "Unit.h"

TurnBar::TurnBar(Scene *scene, std::list<Unit *> allyList,
                 std::list<Unit *> enemyList)
    : GameObject(scene, TextureManager::get("UI-turnBar"),
                 Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 5.3,
                               WIN_HEIGHT - WIN_HEIGHT / 13),
                 Vector2D<int>(WIN_WIDTH / 2, WIN_WIDTH / 16.44)) {
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
    if (i == 0)
      visibleUnits[i] =
          new GameObject(scene_, (*listIt)->getTexture(),
                         Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 1.92 +
                                           (i + 1) * WIN_HEIGHT / 18.18,
                                       WIN_HEIGHT - WIN_HEIGHT / 12.5),
                         Vector2D<int>(WIN_HEIGHT / 5, WIN_HEIGHT / 5));
    else
      visibleUnits[i] = new GameObject(
          scene_, (*listIt)->getTexture(),
          Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 1.9 + (i + 1) * WIN_HEIGHT / 11,
                        WIN_HEIGHT - WIN_HEIGHT / 12.5),
          Vector2D<int>(WIN_HEIGHT / 8, WIN_HEIGHT / 8));
    listIt++;
  }

  selectedUnitSprite =
      new GameObject(scene_, TextureManager::get("UI-circle"),
                     Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 2.05,
                                   WIN_HEIGHT - WIN_HEIGHT / 13),   // pos
                     Vector2D<int>(WIN_WIDTH / 7, WIN_WIDTH / 7));  // tam

  sort();
  unitTurnBar.front()->onSelect();
}

TurnBar::~TurnBar() {
  for (auto unit : visibleUnits) delete unit;
  delete selectedUnitSprite;
}

// takes out the unit in the front of the queue and puts it in the back
void TurnBar::advanceTurn() {
  Unit *frontUnit = unitTurnBar.front();
  if (frontUnit != nullptr) {
    frontUnit->onDeselect();
  }
  unitTurnBar.pop_front();
  unitTurnBar.push_back(frontUnit);
  updateVisibleUnits();
  unitTurnBar.front()->onSelect();
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
  selectedUnitSprite->render();
  for (auto unit : visibleUnits) unit->render();
}

void TurnBar::handleEvents(SDL_Event event) {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_t:
        advanceTurn();
        break;
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

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TurnBar.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Utils/Constants.h"
#include "Unit.h"

TurnBar::TurnBar(Scene *scene, std::list<Unit *> allyList,
                 std::list<Unit *> enemyList)
    : GameObject(
          scene, TextureManager::get("UI-turnBar"),
          Vector2D<int>(static_cast<int>(WIN_WIDTH - WIN_WIDTH / 5.3),
                        WIN_HEIGHT - WIN_HEIGHT / 13),
          Vector2D<int>(WIN_WIDTH / 2, static_cast<int>(WIN_WIDTH / 16.44))) {
  auto allyIt = allyList.begin();
  auto enemyIt = enemyList.begin();
  auto unitCount = 0;

  while (allyIt != allyList.end() || enemyIt != enemyList.end()) {
    if (unitCount % 2 == 0 && allyIt != allyList.end()) {
      unitTurnBar_.push_back(*allyIt);
      ++allyIt;
    } else if (enemyIt != enemyList.end()) {
      unitTurnBar_.push_back(*enemyIt);
      ++enemyIt;
    }
    unitCount++;
  }

  visibleUnits_.resize(visibleTurnBarSize_);
  auto listIt = unitTurnBar_.begin();
  for (Uint32 i = 0; i < visibleTurnBarSize_; i++) {
    if (i == 0)
      visibleUnits_[i] = new GameObject(
          scene_, (*listIt)->getTexture(),
          Vector2D<int>(static_cast<int>(WIN_WIDTH - WIN_WIDTH / 1.92 +
                                         (i + 1.0) * WIN_HEIGHT / 18.18),
                        static_cast<int>(WIN_HEIGHT - WIN_HEIGHT / 12.5)),
          Vector2D<int>(WIN_HEIGHT / 5, WIN_HEIGHT / 5));
    else
      visibleUnits_[i] = new GameObject(
          scene_, (*listIt)->getTexture(),
          Vector2D<int>(static_cast<int>(WIN_WIDTH - WIN_WIDTH / 1.9 +
                                         (i + 1.0) * WIN_HEIGHT / 11.0),
                        static_cast<int>(WIN_HEIGHT - WIN_HEIGHT / 12.5)),
          Vector2D<int>(WIN_HEIGHT / 8, WIN_HEIGHT / 8));
    ++listIt;
  }

  selectedUnitSprite_ = new GameObject(
      scene_, TextureManager::get("UI-circle"),
      Vector2D<int>(static_cast<int>(WIN_WIDTH - WIN_WIDTH / 2.05),
                    WIN_HEIGHT - WIN_HEIGHT / 13),   // pos
      Vector2D<int>(WIN_WIDTH / 7, WIN_WIDTH / 7));  // tam

  sort();
  unitTurnBar_.front()->onSelect();
}

TurnBar::~TurnBar() {
  for (auto unit : visibleUnits_) delete unit;
  delete selectedUnitSprite_;
}

// takes out the unit in the front of the queue and puts it in the back
void TurnBar::advanceTurn() {
  Unit *frontUnit = unitTurnBar_.front();
  if (frontUnit != nullptr) {
    frontUnit->onDeselect();
  }
  unitTurnBar_.pop_front();
  unitTurnBar_.push_back(frontUnit);
  updateVisibleUnits();
  unitTurnBar_.front()->onSelect();
}

void TurnBar::sort() {
  unitTurnBar_.sort([](Unit *unit1, Unit *unit2) {
    return unit1->getStats().speed > unit2->getStats().speed;
  });
  updateVisibleUnits();
}

void TurnBar::eraseUnit(Unit *unit) {
  auto deleted = false;
  auto it = unitTurnBar_.begin();
  while (!deleted && it != unitTurnBar_.end()) {
    if (*it == unit) {
      unitTurnBar_.erase(it);
      deleted = true;

      if (visibleTurnBarSize_ > unitTurnBar_.size()) decreaseVisibleUnitsSize();
    } else {
      ++it;
    }
  }
  updateVisibleUnits();
}

void TurnBar::render() const {
  GameObject::render();
  selectedUnitSprite_->render();
  for (auto unit : visibleUnits_) unit->render();
}

void TurnBar::handleEvents(const SDL_Event event) {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_t:
        advanceTurn();
        break;
      default:
        break;
    }
  }
}

void TurnBar::updateVisibleUnits() {
  auto listIt = unitTurnBar_.begin();
  for (Uint32 i = 0; i < visibleTurnBarSize_; i++) {
    visibleUnits_[i]->setTexture((*listIt)->getTexture());
    ++listIt;
  }
}

void TurnBar::decreaseVisibleUnitsSize() {
  visibleTurnBarSize_--;
  delete visibleUnits_[visibleTurnBarSize_];
  visibleUnits_.resize(visibleTurnBarSize_);
}

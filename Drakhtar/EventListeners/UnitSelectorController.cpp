// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "UnitSelectorController.h"



void UnitSelectorController::addUnitToStore(GameObject * unit)
{
  unitStore.push_back(unit);
}

void UnitSelectorController::addBigUnit(GameObject * unit)
{
  bigUnits.push_back(unit);
  unit->setActive(false);
}

void UnitSelectorController::onClickStop(const SDL_Point point)
{
  cout << "Clicked";

  bool found = false;
  int i;
  for (i = 0; i < unitStore.size(); i++) {
    auto rect = unitStore[i]->getRect();
    if (rect.x < point.x &&
      rect.x + rect.w > point.x &&
      rect.y < point.y &&
      rect.y + rect.h > point.y) {
      found = true;
      break;
    }
  }
  
  if (!found)
    return;

  if (currentVisibleUnit != nullptr) {
    currentVisibleUnit->setActive(false);
  }

  currentVisibleUnit = bigUnits[i];
  currentVisibleUnit->setActive(true);
}

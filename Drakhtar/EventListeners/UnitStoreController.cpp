#include "UnitStoreController.h"
#include "UnitStoreController.h"
// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "UnitStoreController.h"
#include "../Structures/Game.h"
#include "../Scenes/RecruitScene.h"
#include "../Managers/PlayerData.h"
#include "GameObjects/Text.h"


class Text;

void UnitStoreController::increaseAmount(StoreUnit * storeUnit)
{
  auto scene = (RecruitScene*)Game::getSceneMachine()->getCurrentScene();
  if (PlayerData::getInstance()->getMoney() >=
    totalCost + scene->getCost(storeUnit->type_)) {
    totalCost += scene->getCost(storeUnit->type_);
    storeUnit->amount_++;
    storeUnit->amountText_->setText(to_string(storeUnit->amount_));
    scene->updateTotalCostText(totalCost);
  }
}

void UnitStoreController::reduceAmount(StoreUnit * storeUnit)
{
  auto scene = (RecruitScene*)Game::getSceneMachine()->getCurrentScene();
  totalCost -= scene->getCost(storeUnit->type_);
  storeUnit->amount_--;
  storeUnit->amountText_->setText(to_string(storeUnit->amount_));
  scene->updateTotalCostText(totalCost);
}

void UnitStoreController::addUnitToStore(string type, GameObject * unit, Text * amountText, GameObject * moreButton, GameObject * lessButton)
{
  StoreUnit * storeUnit = new StoreUnit(type, unit, amountText, moreButton, lessButton);
  unitStore.push_back(storeUnit);
}


void UnitStoreController::onClickStop(const SDL_Point point)
{

  bool found = false;
  int i;
  for (i = 0; i < unitStore.size(); i++) {

    auto rect = unitStore[i]->lessButton_->getRect();
    if (rect.x < point.x &&
      rect.x + rect.w > point.x &&
      rect.y < point.y &&
      rect.y + rect.h > point.y) {
      if (unitStore[i]->amount_ > 0) {
        reduceAmount(unitStore[i]);
        return;
      }
    }

    rect = unitStore[i]->moreButton_->getRect();
    if (rect.x < point.x &&
      rect.x + rect.w > point.x &&
      rect.y < point.y &&
      rect.y + rect.h > point.y) {
      increaseAmount(unitStore[i]);
      return;
    }

    rect = unitStore[i]->unit_->getRect();
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

  selectedUnit = unitStore[i];
  // TODO: Show and update Unit Parameters Sheet
}

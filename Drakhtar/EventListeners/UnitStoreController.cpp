#include "UnitStoreController.h"
// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "../Managers/PlayerData.h"
#include "../Scenes/RecruitScene.h"
#include "../Structures/Game.h"
#include "GameObjects/Text.h"
#include "Managers/TextureManager.h"
#include "UnitStoreController.h"
#include "Utils/Constants.h"

UnitStoreController::UnitStoreController(GameObject* gameObject)
    : ListenerOnClick(gameObject) {
  acceptButton =
      new GameObject(Game::getInstance()->getSceneMachine()->getCurrentScene(),
                     TextureManager::get("Accept-Button"),
                     Vector2D<int>(WIN_WIDTH / 4 + WIN_WIDTH / 20,
                                   WIN_HEIGHT - WIN_HEIGHT / 13),
                     Vector2D<int>(WIN_WIDTH / 26.6, WIN_HEIGHT / 15));
  Game::getInstance()->getSceneMachine()->getCurrentScene()->addGameObject(
      acceptButton);

  cancelButton =
      new GameObject(Game::getInstance()->getSceneMachine()->getCurrentScene(),
                     TextureManager::get("Cancel-Button"),
                     Vector2D<int>(WIN_WIDTH / 4 - WIN_WIDTH / 20,
                                   WIN_HEIGHT - WIN_HEIGHT / 13),
                     Vector2D<int>(WIN_WIDTH / 26.6, WIN_HEIGHT / 15));
  Game::getInstance()->getSceneMachine()->getCurrentScene()->addGameObject(
      cancelButton);
}

UnitStoreController::~UnitStoreController() {
  while (!unitStore.empty()) {
    delete unitStore.back();
    unitStore.pop_back();
  }
}

void UnitStoreController::increaseAmount(StoreUnit* storeUnit) {
  auto scene = (RecruitScene*)Game::getSceneMachine()->getCurrentScene();
  if (PlayerData::getInstance()->getMoney() >=
      totalCost + scene->getCost(storeUnit->type_)) {
    totalCost += scene->getCost(storeUnit->type_);
    storeUnit->amount_++;
    storeUnit->amountText_->setText(to_string(storeUnit->amount_));
    scene->updateTotalCostText(totalCost);
  }
}

void UnitStoreController::reduceAmount(StoreUnit* storeUnit) {
  auto scene = (RecruitScene*)Game::getSceneMachine()->getCurrentScene();
  totalCost -= scene->getCost(storeUnit->type_);
  storeUnit->amount_--;
  storeUnit->amountText_->setText(to_string(storeUnit->amount_));
  scene->updateTotalCostText(totalCost);
}

void UnitStoreController::buyUnits() {
  auto scene = (RecruitScene*)Game::getSceneMachine()->getCurrentScene();
  for (int i = 0; i < unitStore.size(); i++) {
    if (unitStore[i]->amount_ > 0) {
      scene->buyUnits(unitStore[i]->type_, unitStore[i]->amount_);
      unitStore[i]->amount_ = 0;
      unitStore[i]->amountText_->setText(to_string(0));
    }
  }
  totalCost = 0;
  scene->updateTotalCostText(0);
}

void UnitStoreController::reset() {
  for (int i = 0; i < unitStore.size(); i++) {
    if (unitStore[i]->amount_ > 0) {
      unitStore[i]->amount_ = 0;
      unitStore[i]->amountText_->setText(to_string(0));
    }
  }

  totalCost = 0;
  ((RecruitScene*)Game::getSceneMachine()->getCurrentScene())
      ->updateTotalCostText(0);
}

void UnitStoreController::addUnitToStore(string type, GameObject* unit,
                                         Text* amountText,
                                         GameObject* moreButton,
                                         GameObject* lessButton) {
  StoreUnit* storeUnit =
      new StoreUnit(type, unit, amountText, moreButton, lessButton);
  unitStore.push_back(storeUnit);
}

void UnitStoreController::onClickStop(const SDL_Point point) {
  auto rect = acceptButton->getRect();
  if (rect.x < point.x && rect.x + rect.w > point.x && rect.y < point.y &&
      rect.y + rect.h > point.y) {
    buyUnits();
    return;
  }

  rect = cancelButton->getRect();
  if (rect.x < point.x && rect.x + rect.w > point.x && rect.y < point.y &&
      rect.y + rect.h > point.y) {
    reset();
    return;
  }

  bool found = false;
  int i;
  for (i = 0; i < unitStore.size(); i++) {
    auto rect = unitStore[i]->lessButton_->getRect();
    if (rect.x < point.x && rect.x + rect.w > point.x && rect.y < point.y &&
        rect.y + rect.h > point.y) {
      if (unitStore[i]->amount_ > 0) {
        reduceAmount(unitStore[i]);
        return;
      }
    }

    rect = unitStore[i]->moreButton_->getRect();
    if (rect.x < point.x && rect.x + rect.w > point.x && rect.y < point.y &&
        rect.y + rect.h > point.y) {
      increaseAmount(unitStore[i]);
      return;
    }

    rect = unitStore[i]->unit_->getRect();
    if (rect.x < point.x && rect.x + rect.w > point.x && rect.y < point.y &&
        rect.y + rect.h > point.y) {
      found = true;
      break;
    }
  }

  if (!found) return;

  selectedUnit = unitStore[i];
  // TODO(Carlos): Show and update Unit Parameters Sheet
}

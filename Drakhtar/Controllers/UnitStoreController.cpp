// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitStoreController.h"
#include "../Scenes/RecruitScene.h"
#include "../Structures/Game.h"
#include "GameObjects/RecruitmentStat.h"
#include "GameObjects/Text.h"
#include "Managers/GameManager.h"
#include "Managers/Input.h"
#include "Managers/TextureManager.h"
#include "Utils/Constants.h"

UnitStoreController::UnitStoreController(GameObject* gameObject)
    : ListenerOnClick(gameObject) {
  const auto sceneMachine = Game::getSceneMachine();
  acceptButton_ = new GameObject(
      sceneMachine->getCurrentScene(), TextureManager::get("Accept-Button"),
      Vector2D<int>(WIN_WIDTH / 4 + WIN_WIDTH / 20,
                    WIN_HEIGHT - WIN_HEIGHT / 13),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 26.6), WIN_HEIGHT / 15));
  sceneMachine->getCurrentScene()->addGameObject(acceptButton_);

  cancelButton_ = new GameObject(
      sceneMachine->getCurrentScene(), TextureManager::get("Cancel-Button"),
      Vector2D<int>(WIN_WIDTH / 4 - WIN_WIDTH / 20,
                    WIN_HEIGHT - WIN_HEIGHT / 13),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 26.6), WIN_HEIGHT / 15));
  sceneMachine->getCurrentScene()->addGameObject(cancelButton_);
}

UnitStoreController::~UnitStoreController() {
  while (!unitStore_.empty()) {
    delete unitStore_.back();
    unitStore_.pop_back();
  }
}

void UnitStoreController::increaseAmount(StoreUnit* storeUnit) {
  auto scene = reinterpret_cast<RecruitScene*>(
      Game::getSceneMachine()->getCurrentScene());
  if (GameManager::getInstance()->getMoney() >=
      totalCost_ + scene->getCost(storeUnit->type)) {
    totalCost_ += scene->getCost(storeUnit->type);
    storeUnit->amount++;
    storeUnit->amountText->setText(std::to_string(storeUnit->amount));
    scene->updateTotalCostText(totalCost_);
  }
}

void UnitStoreController::reduceAmount(StoreUnit* storeUnit) {
  auto scene = reinterpret_cast<RecruitScene*>(
      Game::getSceneMachine()->getCurrentScene());
  totalCost_ -= scene->getCost(storeUnit->type);
  storeUnit->amount--;
  storeUnit->amountText->setText(std::to_string(storeUnit->amount));
  scene->updateTotalCostText(totalCost_);
}

void UnitStoreController::buyUnits() {
  auto scene = reinterpret_cast<RecruitScene*>(
      Game::getSceneMachine()->getCurrentScene());
  for (auto& i : unitStore_) {
    if (i->amount > 0) {
      scene->buyUnits(i->type, i->amount);
      i->amount = 0;
      i->amountText->setText(std::to_string(0));
    }
  }
  totalCost_ = 0;
  scene->updateTotalCostText(0);
}

void UnitStoreController::reset() {
  for (auto& i : unitStore_) {
    if (i->amount > 0) {
      i->amount = 0;
      i->amountText->setText(std::to_string(0));
    }
  }

  totalCost_ = 0;
  reinterpret_cast<RecruitScene*>(Game::getSceneMachine()->getCurrentScene())
      ->updateTotalCostText(0);
}

void UnitStoreController::addUnitToStore(const std::string& type,
                                         GameObject* unit, Text* amountText,
                                         GameObject* moreButton,
                                         GameObject* lessButton) {
  const auto storeUnit =
      new StoreUnit(type, unit, amountText, moreButton, lessButton);
  unitStore_.push_back(storeUnit);
}

void UnitStoreController::onClickStop() {
  auto rect = acceptButton_->getRect();
  if (Input::isMouseInside(&rect)) {
    buyUnits();
    return;
  }

  rect = cancelButton_->getRect();
  if (Input::isMouseInside(&rect)) {
    reset();
    return;
  }

  auto found = false;
  size_t i;
  for (i = 0; i < unitStore_.size(); i++) {
    auto rectangle = unitStore_[i]->lessButton->getRect();
    if (Input::isMouseInside(&rectangle)) {
      if (unitStore_[i]->amount > 0) {
        reduceAmount(unitStore_[i]);
        return;
      }
    }

    rectangle = unitStore_[i]->moreButton->getRect();
    if (Input::isMouseInside(&rectangle)) {
      increaseAmount(unitStore_[i]);
      return;
    }

    rectangle = unitStore_[i]->unit->getRect();
    if (Input::isMouseInside(&rectangle)) {
      found = true;
      break;
    }
  }

  if (!found) return;

  selectedUnit_ = unitStore_[i];
  const auto scene = reinterpret_cast<RecruitScene *>(
      Game::getSceneMachine()->getCurrentScene());
  scene->addGameObject(
      new RecruitmentStat(scene, SDL_Rect{100, 100, 110, 110}, selectedUnit_));
  // TODO(Carlos): Show and update Unit Parameters Sheet
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "StoreListener.h"

#include "../Scenes/RecruitScene.h"
#include "../Structures/Game.h"
#include "GameObjects/Button.h"
#include "GameObjects/RecruitmentStat.h"
#include "GameObjects/Text.h"
#include "Managers/FontManager.h"
#include "Managers/GameManager.h"
#include "Managers/Input.h"
#include "Managers/TextureManager.h"
#include "Utils/Constants.h"

StoreListener::StoreListener(GameObject* gameObject, std::string type, int cost)
    : ListenerOnHover(gameObject), storeUnit(type, gameObject, cost) {
  const auto scene = Game::getSceneMachine()->getCurrentScene();

  auto rect = gameObject->getRect();
  const auto h = static_cast<int>(WIN_HEIGHT / 10.14 * 1.5);
  const auto w = static_cast<int>(WIN_WIDTH / 12.92 * 1.5);
  const auto nx = static_cast<int>(WIN_WIDTH / 3.47 - WIN_WIDTH / 12.8);
  const auto px = static_cast<int>(WIN_WIDTH / 3.47 + WIN_WIDTH / 12.8);
  const auto y = rect.y + rect.h / 2;

  auto minusButton = new Button(
      scene, TextureManager::get("Quantity-Button"), Vector2D<int>(nx, y),
      Vector2D<int>(w, h), [this]() {
        if (storeUnit.amount_ > 0) {
          storeUnit.amount_--;
          storeUnit.amountText->setText(std::to_string(storeUnit.amount_));
          reinterpret_cast<RecruitScene*>(
              Game::getSceneMachine()->getCurrentScene())
              ->updateTotalCost(-storeUnit.cost_);
          storeUnit.amountText->setText(std::to_string(storeUnit.amount_));
        }
      });

  minusButton->addChild(new Text(scene, FontManager::get("Retron2000"),
                                 Vector2D<int>(nx, y), {0, 0, 0, 255}, "-",
                                 10));
  gameObject->addChild(minusButton);

  auto plusButton = new Button(
      scene, TextureManager::get("Quantity-Button"), Vector2D<int>(px, y),
      Vector2D<int>(w, h), [this]() {
        auto scene = reinterpret_cast<RecruitScene*>(
            Game::getSceneMachine()->getCurrentScene());
        if (GameManager::getInstance()->getMoney() >=
            scene->getTotalCost() + storeUnit.cost_) {
          scene->updateTotalCost(storeUnit.cost_);
          storeUnit.amount_++;
          storeUnit.amountText->setText(std::to_string(storeUnit.amount_));
        }
      });

  plusButton->addChild(new Text(scene, FontManager::get("Retron2000"),
                                Vector2D<int>(px, y), {0, 0, 0, 255}, "+", 10));

  gameObject->addChild(plusButton);

  storeUnit.amountText =
      new Text(scene, FontManager::get("Retron2000"),
               Vector2D<int>(static_cast<int>(WIN_WIDTH / 3.47), y),
               {0, 0, 0, 255}, "0", 10);

  gameObject->addChild(storeUnit.amountText);
}

StoreListener::~StoreListener() {}

void StoreListener::reset() {
  storeUnit.amount_ = 0;
  storeUnit.amountText->setText(std::to_string(storeUnit.amount_));
}

void StoreListener::onHoverStart() {
  auto rectangle = storeUnit.unit->getRect();
  if (Input::isMouseInside(&rectangle)) {
    std::cout << Input::getMousePosition().getX()
              << Input::getMousePosition().getY();
    const auto scene = reinterpret_cast<RecruitScene*>(
        Game::getSceneMachine()->getCurrentScene());
    scene->addGameObject(
        new RecruitmentStat(scene, SDL_Rect{100, 100, 170, 110}, &storeUnit));
    return;
  }
}

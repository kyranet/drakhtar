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
      Vector2D<int>(w, h),
      [this]() {
        if (storeUnit.amount_ > 0) {
          storeUnit.amount_--;
          storeUnit.amountText->setText(std::to_string(storeUnit.amount_));
          reinterpret_cast<RecruitScene*>(
              Game::getSceneMachine()->getCurrentScene())
              ->updateTotalCost(-storeUnit.cost_);
          storeUnit.amountText->setText(std::to_string(storeUnit.amount_));
          storeUnit.amountText->setColor({255, 255, 255, 0});
        }
      },
      "-", "SkillButtonFont");
  minusButton->setColor({0, 0, 0, 0});
  gameObject->addChild(minusButton);

  auto plusButton = new Button(
      scene, TextureManager::get("Quantity-Button"), Vector2D<int>(px, y),
      Vector2D<int>(w, h),
      [this]() {
        auto scene = reinterpret_cast<RecruitScene*>(
            Game::getSceneMachine()->getCurrentScene());
        auto army = GameManager::getInstance()->getArmy();
        auto capMap = GameManager::getInstance()->getCap();
        if (storeUnit.amount_ + army[storeUnit.type] < capMap[storeUnit.type] &&
            GameManager::getInstance()->getMoney() >=
                scene->getTotalCost() + storeUnit.cost_) {
          scene->updateTotalCost(storeUnit.cost_);
          storeUnit.amount_++;
          storeUnit.amountText->setText(std::to_string(storeUnit.amount_));
          storeUnit.amountText->setColor({255, 255, 255, 0});
        }
      },
      "+", "SkillButtonFont");
  plusButton->setColor({0, 0, 0, 0});
  gameObject->addChild(plusButton);

  auto infoBox =
      new GameObject(scene, TextureManager::get("Reward-Panel"),
                     Vector2D<int>(WIN_WIDTH * 0.68, WIN_HEIGHT * 0.66),
                     Vector2D<int>(WIN_WIDTH * 0.4, WIN_HEIGHT * 0.36));
  auto infoBoxText =
      new Text(scene, FontManager::get("Retron2000"),
               {infoBox->getPosition().getX(),
                infoBox->getPosition().getY() - infoBox->getRect().h / 50},
               {255, 255, 255, 0}, infoFillText(), infoBox->getRect().w * 0.85);
  infoBox->addChild(infoBoxText);
  infoBox->setRenderizable(false);
  gameObject->addChild(infoBox);
  auto infoIcon = new Button(
      scene, TextureManager::get("Quantity-Button"),
      Vector2D<int>(WIN_WIDTH * 0.69, WIN_HEIGHT * 0.9),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 12), WIN_HEIGHT / 5),
      [infoBox]() { infoBox->setRenderizable(!infoBox->getRenderizable()); },
      "?", "SkillButtonFont");
  gameObject->addChild(infoIcon);
  storeUnit.amountText =
      new Text(scene, FontManager::get("Retron2000"),
               Vector2D<int>(static_cast<int>(WIN_WIDTH / 3.47), y),
               {0, 0, 0, 255}, "0", 10);
  storeUnit.amountText->setColor({255, 255, 255, 0});

  gameObject->addChild(storeUnit.amountText);
}

StoreListener::~StoreListener() {}

void StoreListener::reset() {
  storeUnit.amount_ = 0;
  storeUnit.amountText->setText(std::to_string(storeUnit.amount_));
  storeUnit.amountText->setColor({255, 255, 255, 0});
}

std::string StoreListener::infoFillText() const {
  return "-After each fight, the surviving units will be conserved, buying "
         "will increase the number you currently have.\n"
         "-The total amount you buy will be added to one single unit, giving "
         "it more attack power and hp. \n"
         "E.g: having 5 archers will multiply archers stats by 5 \n"
         "-The higher the amount of one unit is, the higher the cost of the "
         "next one will be. \n"
         "-You can buy up to a certain number for each unit. \n"
         "-Matches are turn based, between ally and enemy units altogether, "
         "higher the speed, higher turn priority.";
}

void StoreListener::onHoverStart() {
  auto rectangle = storeUnit.unit->getRect();
  if (Input::isMouseInside(&rectangle) && stats_ == nullptr) {
    const auto scene = reinterpret_cast<RecruitScene*>(
        Game::getSceneMachine()->getCurrentScene());
    stats_ = new RecruitmentStat(scene, &storeUnit);
    scene->addGameObject(stats_);
    return;
  }
}

void StoreListener::onHoverStop() {
  if (stats_ != nullptr) {
    stats_->destroy();
    stats_ = nullptr;
  }
}

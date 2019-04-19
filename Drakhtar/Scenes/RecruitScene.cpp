// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "RecruitScene.h"
#include "EventListeners/StoreListener.h"
#include "GameObjects/Button.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/RecruitmentStat.h"
#include "GameObjects/Text.h"
#include "GameScene.h"
#include "Managers/FontManager.h"
#include "Managers/GameManager.h"
#include "Managers/TextureManager.h"
#include "Structures/Game.h"
#include "TransitionScene.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"

void buttonStartGame() {
  Game::getSceneMachine()->changeScene(new TransitionScene(1));
}

void RecruitScene::preload() {
  GameManager::getInstance()->addMoney(100);

  costs_["Soldier"] = 10;
  costs_["Archer"] = 10;
  costs_["Mage"] = 18;
  costs_["Knight"] = 25;
  costs_["Monster"] = 100;

  const auto background =
      new GameObject(this, TextureManager::get("Recruitment-Background"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));

  moneyText_ = new Text(this, FontManager::get("Retron2000"),
                        Vector2D<int>(static_cast<int>(WIN_WIDTH / 2.55),
                                      WIN_HEIGHT - WIN_HEIGHT / 13),
                        {0, 0, 0, 0}, moneyToString(), WIN_WIDTH);

  totalCostText_ = new Text(this, FontManager::get("Retron2000"),
                            Vector2D<int>(static_cast<int>(WIN_WIDTH / 9.5),
                                          WIN_HEIGHT - WIN_HEIGHT / 13),
                            {0, 0, 0, 0}, "Total cost: 0", 500);

  recruitmentPanel_ =
      new GameObject(this, TextureManager::get("Recruitment-Panel"),
                     Vector2D<int>(WIN_WIDTH / 4, WIN_HEIGHT / 2),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 2.184),
                                   static_cast<int>(WIN_HEIGHT / 1.058)));

  addGameObject(background);
  addGameObject(recruitmentPanel_);

  addUnit("Units-BlueSoldier", 1, costs_["Soldier"]);
  addUnit("Units-BlueArcher", 2, costs_["Archer"]);

  if (GameManager::getInstance()->getLevel() >= 2)
    addUnit("Units-BlueMage", 3, costs_["Mage"]);

  if (GameManager::getInstance()->getLevel() >= 3)
    addUnit("Units-BlueKnight", 4, costs_["Knight"]);

  if (GameManager::getInstance()->getLevel() >= 4)
    addUnit("Units-BlueMonster", 5, costs_["Monster"]);

  addGameObject(totalCostText_);
  addGameObject(moneyText_);

  auto acceptButton = new Button(
      this, TextureManager::get("Accept-Button"),
      Vector2D<int>(WIN_WIDTH / 4 + WIN_WIDTH / 20,
                    WIN_HEIGHT - WIN_HEIGHT / 13),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 26.6), WIN_HEIGHT / 15),
      [this]() {
        for (StoreListener* i : store) {
          auto unit = i->getStoreUnit();
          if (unit.amount_ > 0) {
            GameManager::getInstance()->addUnits(unit.type, unit.amount_);
            GameManager::getInstance()->loseMoney(unit.cost_ * unit.amount_);
            moneyText_->setText(moneyToString());
          }
        }

        reset();
      });

  recruitmentPanel_->addChild(acceptButton);

  auto cancelButton = new Button(
      this, TextureManager::get("Cancel-Button"),
      Vector2D<int>(WIN_WIDTH / 4 - WIN_WIDTH / 20,
                    WIN_HEIGHT - WIN_HEIGHT / 13),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 26.6), WIN_HEIGHT / 15),
      [this]() { reset(); });

  recruitmentPanel_->addChild(cancelButton);

  const auto button = new Button(
      this, TextureManager::get("Button-Play"),
      Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 4, WIN_HEIGHT / 2),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 7.5), WIN_HEIGHT / 12),
      buttonStartGame);

  /*const auto betaInfo =
      new Button(this, TextureManager::get("Button-Play"),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 9.5),
                               WIN_HEIGHT / 2 + WIN_HEIGHT / 6 * -2),
                 Vector2D<int>(WIN_HEIGHT / 6, WIN_HEIGHT / 6), [this]() {
                   addGameObject(new RecruitmentStat(
                       this, SDL_Rect{20, 20, 20, 20}, controller_));
                 });
  addGameObject(betaInfo);*/

  addGameObject(button);
}

int RecruitScene::getCost(const std::string& type) { return costs_[type]; }

void RecruitScene::updateTotalCost(const int amount) {
  totalCost_ += amount;
  totalCostText_->setText("Total cost: " + std::to_string(totalCost_));
}

void RecruitScene::addUnit(std::string textureName, int position, int cost) {
  position -= 3;

  // 4.5 base distance
  // 1280 /  3.47  = 368 = center
  // 1280 / 12.8   = 100 = separator
  // const auto nx = static_cast<int>(WIN_WIDTH / 3.47 - WIN_WIDTH / 12.8);
  //

  auto it = textureName.begin();

  while ((*it) != 'e') ++it;
  ++it;

  std::string type;

  while (it != textureName.end()) {
    type += (*it);
    ++it;
  }
  const auto unit =
      new GameObject(this, TextureManager::get(textureName),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 9.5),
                                   WIN_HEIGHT / 2 + WIN_HEIGHT / 6 * position),
                     Vector2D<int>(WIN_HEIGHT / 6, WIN_HEIGHT / 6));

  addGameObject(unit);

  store.push_back(new StoreListener(unit, type, cost));
  unit->addEventListener(store.back());
}

std::string RecruitScene::moneyToString() const {
  return "Money: " + std::to_string(GameManager::getInstance()->getMoney());
}

void RecruitScene::reset() {
  for (auto i : store)
    if (i->getStoreUnit().amount_ > 0) i->reset();

  totalCost_ = 0;
  updateTotalCost(-totalCost_);
}

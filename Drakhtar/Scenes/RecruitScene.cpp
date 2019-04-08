// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "RecruitScene.h"
#include "EventListeners/UnitStoreController.h"
#include "GameObjects/Button.h"
#include "GameObjects/GameObject.h"
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
  Game::getSceneMachine()->getCurrentScene()->processNextTick(
      []() { Game::getSceneMachine()->changeScene(new TransitionScene(2)); });
}

void RecruitScene::preload() {
  GameManager::getInstance()->addMoney(100);

  costs_["Soldier"] = 10;
  costs_["Archer"] = 10;
  costs_["Mage"] = 13;
  costs_["Knight"] = 20;
  costs_["Monster"] = 18;

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

  controller_ = new UnitStoreController(recruitmentPanel_);
  recruitmentPanel_->addEventListener(controller_);

  addGameObject(totalCostText_);
  addGameObject(moneyText_);

  addUnit("Units-BlueSoldier", 1);
  addUnit("Units-BlueArcher", 2);

  if (GameManager::getInstance()->getLevel() >= 2) addUnit("Units-BlueMage", 3);

  if (GameManager::getInstance()->getLevel() >= 3)
    addUnit("Units-BlueKnight", 4);

  if (GameManager::getInstance()->getLevel() >= 4)
    addUnit("Units-BlueMonster", 5);

  const auto button = new Button(
      this, TextureManager::get("Button-Play"),
      Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 4, WIN_HEIGHT / 2),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 7.5), WIN_HEIGHT / 12),
      buttonStartGame);

  addGameObject(button);
}

int RecruitScene::getCost(const std::string& type) { return costs_[type]; }

void RecruitScene::updateTotalCostText(const int amount) const {
  totalCostText_->setText("Total cost: " + std::to_string(amount));
}

void RecruitScene::addUnit(std::string textureName, int position) {
  position -= 3;

  const auto unit =
      new GameObject(this, TextureManager::get(textureName),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 9.5),
                                   WIN_HEIGHT / 2 + WIN_HEIGHT / 6 * position),
                     Vector2D<int>(WIN_HEIGHT / 6, WIN_HEIGHT / 6));

  addGameObject(unit);

  // 4.5 base distance
  // 1280 /  3.47  = 368 = center
  // 1280 / 12.8   = 100 = separator
  const auto nx = static_cast<int>(WIN_WIDTH / 3.47 - WIN_WIDTH / 12.8);
  const auto px = static_cast<int>(WIN_WIDTH / 3.47 + WIN_WIDTH / 12.8);
  const auto y =
      static_cast<int>(WIN_HEIGHT / 2.0 + WIN_HEIGHT / 6.0 * position);
  auto lessButton = new GameObject(
      this, TextureManager::get("Quantity-Button"), Vector2D<int>(nx, y),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 12.92 * 1.5),
                    static_cast<int>(WIN_HEIGHT / 10.14 * 1.5)));

  lessButton->addChild(new Text(this, FontManager::get("Retron2000"),
                                Vector2D<int>(nx, y), {0, 0, 0, 255}, "-", 10));

  addGameObject(lessButton);

  auto moreButton = new GameObject(
      this, TextureManager::get("Quantity-Button"), Vector2D<int>(px, y),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 12.92 * 1.5),
                    static_cast<int>(WIN_HEIGHT / 10.14 * 1.5)));

  moreButton->addChild(new Text(this, FontManager::get("Retron2000"),
                                Vector2D<int>(px, y), {0, 0, 0, 255}, "+", 10));

  addGameObject(moreButton);

  const auto text =
      new Text(this, FontManager::get("Retron2000"),
               Vector2D<int>(static_cast<int>(WIN_WIDTH / 3.47), y),
               {0, 0, 0, 255}, "0", 10);

  addGameObject(text);

  auto it = textureName.begin();

  while ((*it) != 'e') ++it;
  ++it;

  std::string type;

  while (it != textureName.end()) {
    type += (*it);
    ++it;
  }

  controller_->addUnitToStore(type, unit, text, moreButton, lessButton);
}

std::string RecruitScene::moneyToString() const {
  return "Money: " + std::to_string(GameManager::getInstance()->getMoney());
}

void RecruitScene::buyUnits(const std::string& type, const int quantity) {
  if (costs_[type] * quantity <= GameManager::getInstance()->getMoney()) {
    GameManager::getInstance()->addUnits(type, quantity);
    GameManager::getInstance()->loseMoney(costs_[type] * quantity);
    moneyText_->setText(moneyToString());
  }
}

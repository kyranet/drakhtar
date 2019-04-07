#include "RecruitScene.h"
#include "EventListeners/UnitStoreController.h"
#include "GameObjects/Button.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Text.h"
#include "Managers/FontManager.h"
#include "Managers/PlayerData.h"
#include "Managers/TextureManager.h"
#include "Structures/Game.h"
#include "Structures/UnitFactory.h"
#include "TransitionScene.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"

void buttonStartGame() {
  Game::getSceneMachine()->getCurrentScene()->processNextTick(
      []() { Game::getSceneMachine()->changeScene(new TransitionScene(1)); });
}

void RecruitScene::preload() {
  PlayerData::getInstance()->addMoney(100);

  costs_["Soldier"] = 10;
  costs_["Archer"] = 10;
  costs_["Mage"] = 13;
  costs_["Knight"] = 20;
  costs_["Monster"] = 18;

  const auto background =
      new GameObject(this, TextureManager::get("Recruitment-Background"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));

  moneyText_ =
      new Text(this, FontManager::get("Retron2000"),
               Vector2D<int>(WIN_WIDTH / 2.55, WIN_HEIGHT - WIN_HEIGHT / 13),
               {0, 0, 0, 0}, moneyToString(), WIN_WIDTH);

  totalCostText_ =
      new Text(this, FontManager::get("Retron2000"),
               Vector2D<int>(WIN_WIDTH / 9.5, WIN_HEIGHT - WIN_HEIGHT / 13),
               {0, 0, 0, 0}, "Total cost: 0", 500);

  recruitmentPanel_ =
      new GameObject(this, TextureManager::get("Recruitment-Panel"),
                     Vector2D<int>(WIN_WIDTH / 4, WIN_HEIGHT / 2),
                     Vector2D<int>(WIN_WIDTH / 2.184, WIN_HEIGHT / 1.058));

  addGameObject(background);
  addGameObject(recruitmentPanel_);

  controller_ = new UnitStoreController(recruitmentPanel_);
  recruitmentPanel_->addEventListener(controller_);

  addGameObject(totalCostText_);
  addGameObject(moneyText_);

  addUnit("Units-BlueSoldier", 1);
  addUnit("Units-BlueArcher", 2);

  if (PlayerData::getInstance()->getLevel() >= 2) addUnit("Units-BlueMage", 3);

  if (PlayerData::getInstance()->getLevel() >= 3)
    addUnit("Units-BlueKnight", 4);

  if (PlayerData::getInstance()->getLevel() >= 4)
    addUnit("Units-BlueMonster", 5);

  auto button = new Button(
      this, TextureManager::get("Button-Play"),
      Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 4, WIN_HEIGHT / 2),
      Vector2D<int>(WIN_WIDTH / 7.5, WIN_HEIGHT / 12), buttonStartGame);

  addGameObject(button);
}

int RecruitScene::getCost(string type) { return costs_[type]; }

void RecruitScene::updateTotalCostText(int amount) {
  totalCostText_->setText("Total cost: " + to_string(amount));
}

void RecruitScene::addUnit(string textureName, int position) {
  auto rect = recruitmentPanel_->getRect();

  position -= 3;

  auto unit =
      new GameObject(this, TextureManager::get(textureName),
                     Vector2D<int>(WIN_WIDTH / 9.5,
                                   WIN_HEIGHT / 2 + WIN_HEIGHT / 6 * position),
                     Vector2D<int>(WIN_HEIGHT / 6, WIN_HEIGHT / 6));

  addGameObject(unit);

  // 4.5 distancia base

  // 1280/(3.47)  = 368 = centro
  // 1280/(12.8)   = 100 = separacion

  auto lessButton = new GameObject(
      this, TextureManager::get("Quantity-Button"),
      Vector2D<int>(WIN_WIDTH / 3.47 - WIN_WIDTH / 12.8,
                    WIN_HEIGHT / 2 + WIN_HEIGHT / 6 * position),
      Vector2D<int>(WIN_WIDTH / 12.92 * 1.5, WIN_HEIGHT / 10.14 * 1.5));

  lessButton->addChild(
      new Text(this, FontManager::getInstance()->get("Retron2000"),
               Vector2D<int>(WIN_WIDTH / 3.47 - WIN_WIDTH / 12.8,
                             WIN_HEIGHT / 2 + WIN_HEIGHT / 6 * position),
               {0, 0, 0, 255}, "-", 10));

  addGameObject(lessButton);

  auto moreButton = new GameObject(
      this, TextureManager::get("Quantity-Button"),
      Vector2D<int>(WIN_WIDTH / 3.47 + WIN_WIDTH / 12.8,
                    WIN_HEIGHT / 2 + WIN_HEIGHT / 6 * position),
      Vector2D<int>(WIN_WIDTH / 12.92 * 1.5, WIN_HEIGHT / 10.14 * 1.5));

  moreButton->addChild(
      new Text(this, FontManager::get("Retron2000"),
               Vector2D<int>(WIN_WIDTH / 3.47 + WIN_WIDTH / 12.8,
                             WIN_HEIGHT / 2 + WIN_HEIGHT / 6 * position),
               {0, 0, 0, 255}, "+", 10));

  addGameObject(moreButton);

  auto text =
      new Text(this, FontManager::get("Retron2000"),
               Vector2D<int>(WIN_WIDTH / 3.47,
                             WIN_HEIGHT / 2 + WIN_HEIGHT / 6 * position),
               {0, 0, 0, 255}, "0", 10);

  addGameObject(text);

  auto it = textureName.begin();

  while ((*it) != 'e') it++;
  it++;

  string type = "";

  while (it != textureName.end()) {
    type += (*it);
    it++;
  }

  controller_->addUnitToStore(type, unit, text, moreButton, lessButton);
}

string RecruitScene::moneyToString() {
  return "Money: " + to_string(PlayerData::getInstance()->getMoney());
}

void RecruitScene::buyUnits(string type, int quantity) {
  if (costs_[type] * quantity <= PlayerData::getInstance()->getMoney()) {
    PlayerData::getInstance()->addUnits(type, quantity);
    PlayerData::getInstance()->loseMoney(costs_[type] * quantity);
    moneyText_->setText(moneyToString());
  }
}

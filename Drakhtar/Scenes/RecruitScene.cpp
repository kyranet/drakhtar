#include "RecruitScene.h"
#include "Managers/TextureManager.h"
#include "GameObjects/GameObject.h"
#include "Utils/Constants.h"
#include "EventListeners/UnitSelectorController.h"
#include "Utils/PlayerData.h"
#include "GameObjects/Text.h"
#include "Managers/FontManager.h"
#include "Utils/Vector2D.h"


void RecruitScene::preload()
{
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



	moneyText_ = new Text(this, FontManager::get("Retron2000"),
		Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 7.5, WIN_HEIGHT / 15),
		{ 0,0,0,0 },
		moneyToString(),
		WIN_WIDTH);

	recruitmentPanel =
		new GameObject(this, TextureManager::get("Recruitment-Panel"),
			Vector2D<int>(WIN_WIDTH / 4,
        WIN_HEIGHT / 2),
			Vector2D<int>(WIN_WIDTH / 2.184, 
        WIN_HEIGHT / 1.058 ));



  addGameObject(background);
  addGameObject(moneyText_);
  addGameObject(recruitmentPanel);

  addUnit("Units-BlueSoldier", 1);
  addUnit("Units-BlueArcher", 2);
  addUnit("Units-BlueMage", 3);
  addUnit("Units-BlueKnight", 4);
  addUnit("Units-BlueMonster", 5);
}

void RecruitScene::buyUnits(string type, int quantity)
{
	if (costs_[type] * quantity <= PlayerData::getInstance()->getMoney()) {
		PlayerData::getInstance()->addUnits(type, quantity);
		PlayerData::getInstance()->loseMoney(costs_[type] * quantity);
		moneyText_->setText(moneyToString());
	}
}


void RecruitScene::addUnit(string textureName, int position)
{

	auto rect = recruitmentPanel->getRect();

	position -= 3;

	auto object = new GameObject(this,
		TextureManager::get(textureName),
		Vector2D<int>(WIN_WIDTH / 9.5,
			WIN_HEIGHT /2 + WIN_HEIGHT / 6 * position),
		Vector2D<int>(WIN_HEIGHT / 6,
			WIN_HEIGHT / 6));

  addGameObject(object);

  // 4.5 distancia base

  // 1280/(3.47)  = 368 = centro
  // 1280/(12.8)   = 100 = separacion

  object = new GameObject(this,
    TextureManager::get("Quantity-Button"),
    Vector2D<int>(WIN_WIDTH/ 3.47 - WIN_WIDTH / 12.8,
      WIN_HEIGHT / 2 + WIN_HEIGHT / 6 * position),
    Vector2D<int>(WIN_WIDTH / 12.92 * 1.5,
      WIN_HEIGHT / 10.14 * 1.5));

	addGameObject(object);

  object = new GameObject(this,
    TextureManager::get("Quantity-Button"),
    Vector2D<int>(WIN_WIDTH/3.47 + WIN_WIDTH / 12.8,
      WIN_HEIGHT / 2 + WIN_HEIGHT / 6 * position),
    Vector2D<int>(WIN_WIDTH / 12.92 * 1.5,
      WIN_HEIGHT / 10.14 * 1.5));

  addGameObject(object);
}

string RecruitScene::moneyToString()
{
	return "Money: " + to_string(PlayerData::getInstance()->getMoney());
}

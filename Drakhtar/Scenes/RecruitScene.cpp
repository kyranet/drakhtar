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
		new GameObject(this, TextureManager::get("Maps-SecondBattle"),
			Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
			Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));



	moneyText_ = new Text(this, FontManager::get("Retron2000"),
		Vector2D<int>(WIN_WIDTH / 15 , WIN_HEIGHT / 10),
		{ 0,0,0,0 },
		moneyToString(),
		WIN_WIDTH);

	unitBar_ =
		new GameObject(this, TextureManager::get("UI-turnBar"),
			Vector2D<int>(WIN_WIDTH / 2,
				WIN_HEIGHT - WIN_HEIGHT / 13),
			Vector2D<int>(WIN_WIDTH / 2, 
				WIN_WIDTH / 16.44 ));

  const auto circle = new GameObject(this, TextureManager::get("UI-circle"),
    Vector2D<int>(WIN_WIDTH/ 4,
      WIN_HEIGHT / 2),
    Vector2D<int>(WIN_HEIGHT / 3,
      WIN_HEIGHT / 3));


  addGameObject(background);
  addGameObject(moneyText_);
  addGameObject(unitBar_);
  addGameObject(circle);

  controller_ = new UnitSelectorController(unitBar_);

  unitBar_->addEventListener(controller_);

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

	auto rect = unitBar_->getRect();

	position -= 3;

	auto unit = new GameObject(this,
		TextureManager::get(textureName),
		Vector2D<int>(WIN_WIDTH / 2 + rect.w * position / 6,
			WIN_HEIGHT - WIN_HEIGHT / 13),
		Vector2D<int>(WIN_HEIGHT / 6,
			WIN_HEIGHT / 6));
	controller_->addUnitToStore(unit);

	addGameObject(unit);

	unit = new GameObject(this,
		TextureManager::get(textureName),
		Vector2D<int>(WIN_WIDTH / 4,
			WIN_HEIGHT - WIN_HEIGHT / 2),
		Vector2D<int>(WIN_HEIGHT / 3,
			WIN_HEIGHT / 3));

	controller_->addBigUnit(unit);

	addGameObject(unit);
}

string RecruitScene::moneyToString()
{
	return "Money: " + to_string(PlayerData::getInstance()->getMoney());
}

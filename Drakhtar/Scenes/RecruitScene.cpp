#include "RecruitScene.h"
#include "Managers/TextureManager.h"
#include "GameObjects/GameObject.h"
#include "Utils/Constants.h"
#include "EventListeners/UnitSelectorController.h"


void RecruitScene::addUnit(string textureName, int position)
{

  auto rect = unitBar->getRect();

  position -= 3;

  auto unit = new GameObject(this,
    TextureManager::get(textureName),
    Vector2D<int>(WIN_WIDTH / 2 + rect.w * position / 6,
      WIN_HEIGHT - WIN_HEIGHT / 13),
    Vector2D<int>(WIN_HEIGHT / 6,
      WIN_HEIGHT / 6));
  controller->addUnitToStore(unit);

  addGameObject(unit);

  unit = new GameObject(this,
    TextureManager::get(textureName),
    Vector2D<int>(WIN_WIDTH / 4,
      WIN_HEIGHT - WIN_HEIGHT / 2),
    Vector2D<int>(WIN_HEIGHT / 3,
      WIN_HEIGHT / 3));

  controller->addBigUnit(unit);

  addGameObject(unit);
}

void RecruitScene::preload()
{
	const auto background =
		new GameObject(this, TextureManager::get("Maps-SecondBattle"),
			Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
			Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));

	unitBar =
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
  addGameObject(unitBar);
  addGameObject(circle);

  controller = new UnitSelectorController(unitBar);

  unitBar->addEventListener(controller);

  addUnit("Units-BlueSoldier", 1);
  addUnit("Units-BlueArcher", 2);
  addUnit("Units-BlueMage", 3);
  addUnit("Units-BlueKnight", 4);
  addUnit("Units-BlueMonster", 5);
}

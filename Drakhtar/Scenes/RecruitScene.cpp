#include "RecruitScene.h"
#include "Managers/TextureManager.h"
#include "GameObjects/GameObject.h"
#include "Utils/Constants.h"
#include "EventListeners/ListenerOnClick.h"

void RecruitScene::preload()
{
	const auto background =
		new GameObject(this, TextureManager::get("Maps-SecondBattle"),
			Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
			Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));

	const auto unitList =
		new GameObject(this, TextureManager::get("UI-turnBar"),
			Vector2D<int>(WIN_WIDTH / 2,
				WIN_HEIGHT - WIN_HEIGHT / 13),
			Vector2D<int>(WIN_WIDTH / 2, 
				WIN_WIDTH / 16.44 ));

	const auto unitSelector =
		new GameObject(this, nullptr,
			Vector2D<int>(WIN_WIDTH / 2,
				WIN_HEIGHT - WIN_HEIGHT / 13),
			Vector2D<int>(WIN_WIDTH / 2,
				WIN_HEIGHT / 5));

	soldier =
		new GameObject(this, TextureManager::get("Units-BlueSoldier"),
			Vector2D<int>(WIN_WIDTH / 2,
				WIN_HEIGHT - WIN_HEIGHT / 13),
			Vector2D<int>(WIN_HEIGHT / 5, WIN_HEIGHT / 5));

	soldier->addEventListener(new ListenerOnClick(soldier));


	addGameObject(background);
	addGameObject(unitList);
	addGameObject(soldier);
}

void RecruitScene::update()
{
	if(soldier.ev)
}

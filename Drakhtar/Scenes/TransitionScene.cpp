#include "TransitionScene.h"
#include "GameScene.h"
#include "../Structures/Game.h"
#include "../GameObjects/GameObject.h"
#include "../Managers/TextureManager.h"
#include "../GameObjects/DialogScene.h"
#include "../Utils/Constants.h"

TransitionScene::TransitionScene(int battle) : battle_(battle)
{

}

void TransitionScene::preload()
{
	const auto background =
		new GameObject(this, TextureManager::get("Transition-Map" + std::to_string(battle_)),
			Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
			Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
	addGameObject(background);
	
	auto dialog = new DialogScene(this, "dialog1_start", "DialogFont");
	addGameObject(dialog);
	setTransition(true);
}

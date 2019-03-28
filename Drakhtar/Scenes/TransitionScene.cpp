#include "TransitionScene.h"

void TransitionScene::preload()
{
	const auto background =
		new GameObject(this, TextureManager::get("Maps-SecondBattle"),
			Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
			Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
	addGameObject(background);

	auto dialog = new DialogScene(this, "dialog1_start", "DialogFont");
	addGameObject(dialog);
}

#include "RecruitmentStat.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Structures/Font.h"
#include "../Utils/Constants.h"
RecruitmentStat::RecruitmentStat(Scene *scene, SDL_Rect BoxArea) : GameObject(scene, nullptr, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
	Vector2D<int>(1, 1))
{
	const auto boxImage = new GameObject(
		scene, TextureManager::get(imageText_),
		Vector2D<int>(tutorialArea.x,
			dialogueBackground.y + dialogueBackground.h / 3),
		Vector2D<int>(tutorialArea.h * WIN_WIDTH / 4,
			tutorialArea.h * WIN_HEIGHT / 4));
			addchild
}

RecruitmentStat::~RecruitmentStat()
{
}

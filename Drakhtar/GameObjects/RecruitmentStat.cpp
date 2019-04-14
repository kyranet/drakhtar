#include "RecruitmentStat.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Structures/Font.h"
#include "../Utils/Constants.h"
RecruitmentStat::RecruitmentStat(Scene *scene, SDL_Rect BoxArea)
    : GameObject(scene, nullptr, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                 Vector2D<int>(1, 1)) {
  const auto boxImage = new GameObject(
      scene, TextureManager::get("UI-tutorialBackground"),
      Vector2D<int>(200, 200),
      Vector2D<int>(100,100));
  addChild(boxImage);
}

RecruitmentStat::~RecruitmentStat() {}

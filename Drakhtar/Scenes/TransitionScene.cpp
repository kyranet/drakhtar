// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TransitionScene.h"
#include "../GameObjects/DialogScene.h"
#include "../GameObjects/GameObject.h"
#include "../Managers/TextureManager.h"
#include "../Structures/Game.h"
#include "../Utils/Constants.h"
#include "GameScene.h"

TransitionScene::TransitionScene(const int battle) : battle_(battle) {}

void TransitionScene::preload() {
  const auto background = new GameObject(
      this, TextureManager::get("Transition-Map" + std::to_string(battle_)),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
      Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  addGameObject(background);

  const auto dialog = new DialogScene(this, "dialog1_intro", "DialogFont");
  addGameObject(dialog);
  setTransition(true);
}

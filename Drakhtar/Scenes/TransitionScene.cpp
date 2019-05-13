// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TransitionScene.h"

#include "../GameObjects/DialogScene.h"
#include "../GameObjects/GameObject.h"
#include "../Managers/TextureManager.h"
#include "../Structures/Game.h"
#include "../Utils/Constants.h"
#include "GameScene.h"
#include "Managers/SDLAudioManager.h"

TransitionScene::TransitionScene(const int battle) : battle_(battle) {}

void TransitionScene::preload() {
  SDLAudioManager::getInstance()->haltMusic();
  switch (battle_) {
    case 1:
      SDLAudioManager::getInstance()->playMusic(8, 999);
      break;
    case 2:
      SDLAudioManager::getInstance()->playMusic(9, 999);
      break; 
	case 3:
      SDLAudioManager::getInstance()->playMusic(10, 999);
      break;
    default:
      break;
  }
  const auto background = new GameObject(
      this, TextureManager::get("Transition-Map" + std::to_string(battle_)),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
      Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  addGameObject(background);

  const auto dialog = new DialogScene(
      this, "dialog" + std::to_string(battle_) + "transition", "DialogFont");
  addGameObject(dialog);
  setTransition(true);
}

int TransitionScene::getBattleInd() { return battle_; }

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "MenuScene.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/GameObject.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/TransitionScene.h"
#include "../Structures/Game.h"
#include "../Utils/Constants.h"
#include "../Utils/Vector2D.h"
#include "Managers/SDLAudioManager.h"
#include "RecruitScene.h"

void buttonPlay() {
  Game::getSceneMachine()->getCurrentScene()->processNextTick([]() {
    Game::getSceneMachine()->changeScene(new TransitionScene(1.0));
    SDLAudioManager::getInstance()->playChannel(2, 0, 0);
  });
}

void buttonOptions() { std::cout << "Options\n"; }

void MenuScene::preload() {
  Scene::preload();
  const auto background =
      new GameObject(this, TextureManager::get("Maps-Test"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  const auto play = new Button(
      this, TextureManager::get("Button-Play"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 - WIN_HEIGHT / 18),
      Vector2D<int>(static_cast<int>(floor(WIN_WIDTH / 7.5)), WIN_HEIGHT / 12),
      buttonPlay);
  const auto options = new Button(
      this, TextureManager::get("Button-Options"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 + WIN_HEIGHT / 18),
      Vector2D<int>(static_cast<int>(floor(WIN_WIDTH / 7.5)), WIN_HEIGHT / 12),
      buttonOptions);

  auto audio = SDLAudioManager::getInstance();
  audio->haltChannel(0);
  audio->haltMusic();
  audio->playMusic(0, -1);
  audio->setMusicVolume(30);
  addGameObject(background);
  addGameObject(play);
  addGameObject(options);
}

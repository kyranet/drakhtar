// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
#include "MenuScene.h"

#include "../GameObjects/Button.h"
#include "../GameObjects/GameObject.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/TransitionScene.h"
#include "../Structures/Game.h"
#include "../Utils/Constants.h"
#include "../Utils/Vector2D.h"
#include "GameObjects/OptionsMenu.h"
#include "Managers/SDLAudioManager.h"
#include "RecruitScene.h"

void buttonPlay() {
  Game::getSceneMachine()->changeScene(new RecruitScene());
  SDLAudioManager::getInstance()->playChannel(2, 0, 0);
}

void MenuScene::preload() {
  Scene::preload();
  const auto background =
      new GameObject(this, TextureManager::get("Transition-Menu"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  const auto play = new Button(
      this, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 - WIN_HEIGHT / 18),
      Vector2D<int>(static_cast<int>(floor(WIN_WIDTH / 7.5)), WIN_HEIGHT / 12),
      buttonPlay, "Play", "ButtonFont");
  const auto options = new Button(
      this, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 + WIN_HEIGHT / 18),
      Vector2D<int>(static_cast<int>(floor(WIN_WIDTH / 7.5)), WIN_HEIGHT / 12),
      [this]() { this->addGameObject(new OptionsMenu(this)); }, "Options",
      "ButtonFont");

  auto audio = SDLAudioManager::getInstance();
  audio->haltChannel(0);
  audio->haltMusic();
  audio->playMusic(0, -1);
  if (audio->getDefault()) audio->setMusicVolume(30);
  addGameObject(background);
  addGameObject(play);
  addGameObject(options);
}

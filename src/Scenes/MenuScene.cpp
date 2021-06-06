// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "MenuScene.h"

#include "GameObjects/Button.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/OptionsMenu.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/TextureManager.h"
#include "RecruitScene.h"
#include "Scenes/TransitionScene.h"
#include "Structures/Game.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"

void buttonPlay() {
  Game::getSceneMachine()->changeScene(new TransitionScene(1));
  SDLAudioManager::getInstance()->playChannel(2, 0, 0);
}

void MenuScene::preload() {
  Scene::preload();
  const auto background =
      new GameObject(this, TextureManager::get("Transition-Menu"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  const auto vg = new GameObject(this, TextureManager::get("Logos-VG"),
                                 Vector2D<int>(WIN_WIDTH - 50, WIN_HEIGHT - 40),
                                 Vector2D<int>(100, 75));
  const auto logo =
      new GameObject(this, TextureManager::get("Logos-logo"),
                     Vector2D<int>(WIN_WIDTH / 2, (WIN_HEIGHT / 2) - 150),
                     Vector2D<int>(800, 400));
  const auto play = new Button(
      this, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 + WIN_HEIGHT / 60),
      Vector2D<int>(static_cast<int>(floor(WIN_WIDTH / 5.5)), WIN_HEIGHT / 10),
      buttonPlay, Game::getInstance()->getLocale()->get("PLAY").run({}),
      "ButtonFont");
  const auto options = new Button(
      this, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 + (WIN_HEIGHT / 60 + 80)),
      Vector2D<int>(static_cast<int>(floor(WIN_WIDTH / 5.5)), WIN_HEIGHT / 10),
      [this]() { this->addGameObject(new OptionsMenu(this)); },
      Game::getInstance()->getLocale()->get("OPTIONS").run({}), "ButtonFont");
  const auto exitButton = new Button(
      this, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 + (WIN_HEIGHT / 60 + 160)),
      Vector2D<int>(static_cast<int>(floor(WIN_WIDTH / 5.5)), WIN_HEIGHT / 10),
      [this]() { finish(true); },
      Game::getInstance()->getLocale()->get("EXITGAME").run({}), "ButtonFont");

  auto audio = SDLAudioManager::getInstance();
  audio->haltChannel(0);
  audio->haltMusic();
  audio->playMusic(0, -1);
  if (audio->getDefault()) audio->setMusicVolume(30);
  addGameObject(background);
  addGameObject(vg);
  addGameObject(logo);
  addGameObject(play);
  addGameObject(options);
  addGameObject(exitButton);
}

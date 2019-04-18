// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Pause.h"
#include "Button.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/Scene.h"
#include "Structures/Game.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"

Pause::Pause(Scene* scene) : GameObject(scene, nullptr) {
  const auto panel =
      new GameObject(scene_, TextureManager::get("Pause-Panel"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 4.68),
                                   static_cast<int>(WIN_HEIGHT / 2.25)));
  const auto restart = 
	  new Button(scene_, nullptr,
				 Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
				 Vector2D<int>(static_cast<int>(WIN_WIDTH / 8.33),
			   				   static_cast<int>(WIN_HEIGHT / 11.25)),
				 []() { Game::getSceneMachine()->changeScene(new GameScene(1)); 
				 },
				 "Restart", "TutorialFont");
  const auto exit =
      new Button(scene_, TextureManager::get("Vanilla-Button"),
                 Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 + 70),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 8.33),
                               static_cast<int>(WIN_HEIGHT / 11.25)),
                 []() {
                   Game::getSceneMachine()->changeScene(new MenuScene());
                   SDLAudioManager::getInstance()->playChannel(6, 0, 0);
                 },
                 "Exit", "TutorialFont");

  const auto resume =
      new Button(scene_, TextureManager::get("Vanilla-Button"),
                 Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 - 70),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 8.33),
                               static_cast<int>(WIN_HEIGHT / 11.25)),
                 [this]() {
                   destroy();
                   scene_->resume();
                 },
                 "Resume", "TutorialFont");

  addChild(panel);
  addChild(restart);
  addChild(exit);
  addChild(resume);
}


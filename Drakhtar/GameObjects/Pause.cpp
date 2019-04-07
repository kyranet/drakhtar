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

void restartGame() {
  Game::getSceneMachine()->getCurrentScene()->processNextTick(
      []() { Game::getSceneMachine()->changeScene(new GameScene()); });
}

void exitGame() {
  Game::getSceneMachine()->getCurrentScene()->processNextTick(
      []() { Game::getSceneMachine()->changeScene(new MenuScene()); });
  SDLAudioManager::getInstance()->playChannel(6, 0, 0);
}

Pause::Pause(Scene *scene) : GameObject(scene, nullptr) {
  const auto panel =
      new GameObject(scene_, TextureManager::get("Pause-Panel"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 4.68),
                                   static_cast<int>(WIN_HEIGHT / 2.25)));
  const auto restart =
      new Button(scene_, TextureManager::get("Button-Restart"),
                 Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 - WIN_HEIGHT / 18),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 8.33),
                               static_cast<int>(WIN_HEIGHT / 11.25)),
                 restartGame);
  const auto exit =
      new Button(scene_, TextureManager::get("Button-Exit"),
                 Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 + WIN_HEIGHT / 18),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 8.33),
                               static_cast<int>(WIN_HEIGHT / 11.25)),
                 exitGame);

  addChild(panel);
  addChild(restart);
  addChild(exit);
}

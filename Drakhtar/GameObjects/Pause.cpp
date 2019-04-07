// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Pause.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/GameScene.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/Scene.h"
#include "../Structures/Game.h"
#include "../Utils/Constants.h"
#include "../Utils/Vector2D.h"
#include "Button.h"

void restartGame() {
  Game::getSceneMachine()->getCurrentScene()->processNextTick(
      []() { Game::getSceneMachine()->changeScene(new GameScene()); });
}

void exitGame() {
  Game::getSceneMachine()->getCurrentScene()->processNextTick(
      []() { Game::getSceneMachine()->changeScene(new MenuScene()); });
}
void buttonResume() {
  Game::getSceneMachine()->getCurrentScene()->pause();
  //Game::getSceneMachine()->getCurrentScene()->removeGameObject(this);
}

Pause::Pause(Scene *scene) : GameObject(scene, nullptr) {
  auto panel =
      new GameObject(scene_, TextureManager::get("Pause-Panel"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(WIN_WIDTH / 4.68, WIN_HEIGHT / 2.25));
  auto restart = new Button(
      scene_, TextureManager::get("Button-Restart"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 - WIN_HEIGHT / 18),
      Vector2D<int>(WIN_WIDTH / 8.33, WIN_HEIGHT / 11.25), restartGame);
  auto exit =
      new Button(scene_, TextureManager::get("Button-Exit"),
                 Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 + WIN_HEIGHT / 18),
                 Vector2D<int>(WIN_WIDTH / 8.33, WIN_HEIGHT / 11.25), exitGame);

  auto resumeButton = new Button(
      scene_, TextureManager::get("Button-Resume"),
      Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 24, WIN_HEIGHT / 18),
      Vector2D<int>(WIN_WIDTH / 21.6, WIN_HEIGHT / 14.4), buttonResume);

  addChild(panel);
  addChild(restart);
  scene_->addGameObject(resumeButton);
  addChild(exit);
}

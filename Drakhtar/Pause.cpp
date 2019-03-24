// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Pause.h"
#include "Button.h"
#include "Constants.h"
#include "Game.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "Scene.h"
#include "TextureManager.h"
#include "Vector2D.h"

void restartGame() {
  Game::getSceneMachine()->getCurrentScene()->processNextTick(
      []() { Game::getSceneMachine()->changeScene(new GameScene()); });
}

void exitGame() {
  Game::getSceneMachine()->getCurrentScene()->processNextTick(
      []() { Game::getSceneMachine()->changeScene(new MenuScene()); });
}

Pause::Pause(Scene *scene) : GameObject(scene, nullptr) {
  auto panel = new GameObject(scene_, TextureManager::get("Pause-Panel"),
                              Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                              Vector2D<int>(400, 500));
  auto restart = new Button(scene_, TextureManager::get("Button-Restart"),
                            Vector2D<int>(WIN_WIDTH / 2, 250),
                            Vector2D<int>(225, 100), restartGame);
  auto exit = new Button(scene_, TextureManager::get("Button-Exit"),
                         Vector2D<int>(WIN_WIDTH / 2, 350),
                         Vector2D<int>(225, 100), exitGame);

  addChild(panel);
  addChild(restart);
  addChild(exit);
}

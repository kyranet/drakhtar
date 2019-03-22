// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "PauseScene.h"
#include "Button.h"
#include "Game.h"
#include "GameObject.h"
#include "MenuScene.h"

void PauseScene::preload() {
  auto panel = new GameObject(TextureManager::get("Pause-Panel"),
                              Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                              Vector2D<int>(400, 500));
  auto restart = new Button(TextureManager::get("Button-Restart"),
                            WIN_WIDTH / 2, 250, 225, 100, RestartGame);
  auto exit = new Button(TextureManager::get("Button-Exit"), WIN_WIDTH / 2, 350,
                         225, 100, ExitGame, game_, renderer_);

  addGameObject(panel);
  addGameObject(restart);
  addGameObject(exit);
}

void restartGame() {
  Game::getStateMachine()->pushState(new State(game, renderer));
}

void exitGame() {
  Game::getStateMachine()->pushState(new MenuScene(game, renderer));
}

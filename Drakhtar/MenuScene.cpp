// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "MenuScene.h"
#include "Button.h"
#include "Game.h"
#include "GameObject.h"

void MenuScene::preload() {
  auto background = new GameObject(TextureManager::get("Maps-Test"),
                                   Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                                   Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  auto play = new Button(TextureManager::get("Button-Play"), WIN_WIDTH / 2, 250,
                         200, 75, buttonPlay);
  auto options = new Button(TextureManager::get("Button-Options"),
                            WIN_WIDTH / 2, 350, 200, 75, buttonOptions);

  addGameObject(background);
  addGameObject(play);
  addGameObject(options);
}

void buttonPlay() {
  Game::getStateMachine()->pushState(new GameState());
  cout << "Play\n";
}

void buttonOptions() { cout << "Options\n"; }

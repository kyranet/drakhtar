// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "MenuScene.h"
#include "Button.h"
#include "Constants.h"
#include "Game.h"
#include "GameObject.h"
#include "GameScene.h"
#include "TextureManager.h"
#include "Vector2D.h"

void buttonPlay() { Game::getSceneMachine()->changeScene(new GameScene()); }

void buttonOptions() { cout << "Options\n"; }

void MenuScene::preload() {
  auto background = new GameObject(this, TextureManager::get("Maps-Test"),
                                   Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                                   Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  auto play = new Button(this, TextureManager::get("Button-Play"),
                         Vector2D<int>(WIN_WIDTH / 2, 250),
                         Vector2D<int>(200, 75), buttonPlay);
  auto options = new Button(this, TextureManager::get("Button-Options"),
                            Vector2D<int>(WIN_WIDTH / 2, 350),
                            Vector2D<int>(200, 75), buttonOptions);

  addGameObject(background);
  addGameObject(play);
  addGameObject(options);
}

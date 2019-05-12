// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameOverPanel.h"

#include "Button.h"
#include "Managers/FontManager.h"
#include "Managers/TextureManager.h"
#include "Scenes/CreditsScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/RecruitScene.h"
#include "Scenes/Scene.h"
#include "Scenes/TransitionScene.h"
#include "Structures/Game.h"
#include "Text.h"
#include "Utils/Constants.h"
GameOverPanel::GameOverPanel(Scene* scene, Texture* texture,
                             const Vector2D<int>& position,
                             const Vector2D<int>& size, bool victory)
    : GameObject(scene, texture, position, size) {
  const auto continueButton_ = new Button(
      scene, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(position.getX(), position.getY() + size.getY() / 4),
      Vector2D<int>(size.getX() / 4, size.getY() / 4),
      [this, victory]() {
        int currentScene =
            reinterpret_cast<GameScene*>(getScene())->getBattleInd();
        if (victory) {
          if (currentScene < 1) {  // 5 meaning five levels plus last scene
                                   // before returning to main menu
            Game::getSceneMachine()->changeScene(
                new RecruitScene(currentScene + 1));
          } else {
            Game::getSceneMachine()->changeScene(new CreditsScene());
          }
        } else {
          Game::getSceneMachine()->changeScene(new GameScene(currentScene));
        }
      },
      "Continue", "ButtonFont");

  const auto text_ =
      new Text(scene_, FontManager::get("ButtonFontBig"), position,
               {0, 0, 0, 1}, "VICTORY", this->getRect().w);
  if (!victory) {
    text_->setText("DEFEAT");
  }

  addChild(text_);
  addChild(continueButton_);
}

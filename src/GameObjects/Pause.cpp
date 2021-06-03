// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Pause.h"

#include "Button.h"
#include "Managers/GameManager.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/RecruitScene.h"
#include "Scenes/Scene.h"
#include "Structures/Game.h"
#include "Tracker.h"
#include "TrackerEvents/LevelEndEvent.h"
#include "TrackerEvents/PauseEndEvent.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"

Pause::Pause(Scene* scene) : GameObject(scene, nullptr) {
  const auto panel =
      new GameObject(scene_, TextureManager::get("Pause-Panel"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 4.68),
                                   static_cast<int>(WIN_HEIGHT / 2.25)));
  const auto restart = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 8.33),
                    static_cast<int>(WIN_HEIGHT / 11.25)),
      [scene]() {
        GameScene* gameScene = reinterpret_cast<GameScene*>(scene);
        int battleInd = reinterpret_cast<GameScene*>(scene)->getBattleInd();
        Tracker::getInstance().trackEvent(new PauseEndEvent(battleInd));
        Tracker::getInstance().trackEvent(
            new LevelEndEvent(gameScene->getBattleInd(), LevelResult::RESTART,
                              gameScene->getPlayerArmy()));
        Game::getSceneMachine()->changeScene(new GameScene(battleInd));
      },
      Game::getInstance()->getLocale()->get("RESTART").run({}), "ButtonFont");
  const auto exit = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 + 70),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 8.33),
                    static_cast<int>(WIN_HEIGHT / 11.25)),
      [scene]() {
        GameScene* gameScene = reinterpret_cast<GameScene*>(scene);

        Tracker::getInstance().trackEvent(
            new PauseEndEvent(gameScene->getBattleInd()));
        Tracker::getInstance().trackEvent(
            new LevelEndEvent(gameScene->getBattleInd(), LevelResult::QUIT,
                              gameScene->getPlayerArmy()));

        GameManager::getInstance()->reset();
        Game::getSceneMachine()->changeScene(new MenuScene());
        SDLAudioManager::getInstance()->playChannel(6, 0, 0);
      },
      Game::getInstance()->getLocale()->get("EXIT").run({}), "ButtonFont");

  const auto resume = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2 - 70),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 8.33),
                    static_cast<int>(WIN_HEIGHT / 11.25)),
      [this, scene]() {
        GameScene* gameScene = reinterpret_cast<GameScene*>(scene);

        Tracker::getInstance().trackEvent(
            new PauseEndEvent(gameScene->getBattleInd()));

        destroy();
        scene_->resume();
      },
      Game::getInstance()->getLocale()->get("RESUME").run({}), "ButtonFont");

  addChild(panel);
  addChild(restart);
  addChild(exit);
  addChild(resume);
}

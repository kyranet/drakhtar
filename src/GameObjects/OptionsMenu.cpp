// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "OptionsMenu.h"

#include "GameObjects/Button.h"
#include "GameObjects/Text.h"
#include "Managers/FontManager.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/TextureManager.h"
#include "Scenes/MenuScene.h"
#include "Structures/Game.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"

OptionsMenu::OptionsMenu(Scene* scene) : GameObject(scene, nullptr) {
  const auto panel = new GameObject(
      scene_, TextureManager::get("UI-WhiteBox"),
      {static_cast<int>(WIN_WIDTH / 2.0), static_cast<int>(WIN_HEIGHT / 2.0)},
      {static_cast<int>(WIN_WIDTH / 4.0), static_cast<int>(WIN_HEIGHT / 3.0)});
  const auto returnButton = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      {static_cast<int>(WIN_WIDTH / 2.0), static_cast<int>(WIN_HEIGHT / 1.65)},
      {static_cast<int>(WIN_WIDTH / 10.0), static_cast<int>(WIN_HEIGHT / 8.0)},
      [this]() { destroy(); },
      Game::getInstance()->getLocale()->format("RETURN"), "ButtonFont");
  const auto soundIcon = new GameObject(
      scene_, TextureManager::get("UI-ActiveSound"),
      {static_cast<int>(WIN_WIDTH / 2.0), static_cast<int>(WIN_HEIGHT / 2.25)},
      {static_cast<int>(WIN_WIDTH / 25.0),
       static_cast<int>(WIN_HEIGHT / 20.0)});
  const auto muteIcon = new GameObject(
      scene_, TextureManager::get("UI-MuteSound"),
      {static_cast<int>(WIN_WIDTH / 2.0), static_cast<int>(WIN_HEIGHT / 2.25)},
      {static_cast<int>(WIN_WIDTH / 25.0),
       static_cast<int>(WIN_HEIGHT / 20.0)});
  const auto greenTick = new GameObject(
      scene_, TextureManager::get("UI-greenTick"),
      {static_cast<int>(WIN_WIDTH / 2.20), static_cast<int>(WIN_HEIGHT / 1.95)},
      {static_cast<int>(WIN_WIDTH / 17.0),
       static_cast<int>(WIN_HEIGHT / 12.0)});

  const auto audio = SDLAudioManager::getInstance();
  greenTick->setTransparent(true);
  greenTick->setRenderable(audio->getDefault());
  muteIcon->setRenderable(audio->getMusicVolume() == 0);
  soundIcon->setRenderable(audio->getMusicVolume() != 0);

  const auto moreSoundBox = new Button(
      scene_, TextureManager::get("Quantity-Button"),
      {static_cast<int>(WIN_WIDTH / 1.75), static_cast<int>(WIN_HEIGHT / 2.25)},
      {static_cast<int>(WIN_WIDTH / 15), static_cast<int>(WIN_HEIGHT / 8)},
      [muteIcon, soundIcon]() {
        const auto manager = SDLAudioManager::getInstance();
        if (!manager->getDefault() && manager->getMusicVolume() < 100) {
          manager->setChannelVolume(manager->getChannelVolume() + 10, 0);
          manager->setChannelVolume(manager->getChannelVolume() + 10, 1);
          manager->setMusicVolume(manager->getMusicVolume() + 10);

          muteIcon->setRenderable(manager->getMusicVolume() == 0);
          soundIcon->setRenderable(manager->getMusicVolume() != 0);
        }
      },
      "+", "StatsFont");
  const auto LessSoundBox = new Button(
      scene_, TextureManager::get("Quantity-Button"),
      {static_cast<int>(WIN_WIDTH / 2.35), static_cast<int>(WIN_HEIGHT / 2.25)},
      {static_cast<int>(WIN_WIDTH / 15), static_cast<int>(WIN_HEIGHT / 8)},
      [muteIcon, soundIcon]() {
        const auto manager = SDLAudioManager::getInstance();
        if (!manager->getDefault() && manager->getMusicVolume() > 0) {
          manager->setChannelVolume(manager->getChannelVolume() - 10, 0);
          manager->setChannelVolume(manager->getChannelVolume() - 10, 1);
          manager->setMusicVolume(manager->getMusicVolume() - 10);

          muteIcon->setRenderable(manager->getMusicVolume() == 0);
          soundIcon->setRenderable(manager->getMusicVolume() != 0);
        }
      },
      "-", "StatsFont");

  const auto DefaultText = new Text(
      scene_, FontManager::get("StatsFont"),
      {static_cast<int>(WIN_WIDTH / 1.9), static_cast<int>(WIN_HEIGHT / 1.9)},
      {0, 0, 0, 0}, Game::getInstance()->getLocale()->format("DEFAULT"), 10000);
  const auto defaultButton = new Button(
      scene_, TextureManager::get("UI-cellFrame"),
      {static_cast<int>(WIN_WIDTH / 2.25), static_cast<int>(WIN_HEIGHT / 1.9)},
      {static_cast<int>(WIN_WIDTH / 35.0), static_cast<int>(WIN_WIDTH / 35.0)},
      [greenTick]() {
        const auto manager = SDLAudioManager::getInstance();
        manager->setDefault(!manager->getDefault());
        greenTick->setRenderable(manager->getDefault());
      },
      " ", "ButtonFont");

  addChild(panel);
  addChild(returnButton);
  addChild(moreSoundBox);
  addChild(LessSoundBox);
  addChild(DefaultText);
  addChild(defaultButton);
  addChild(greenTick);
  addChild(muteIcon);
  addChild(soundIcon);
}

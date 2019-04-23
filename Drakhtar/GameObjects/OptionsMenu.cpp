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
/*GameObject* greenTick;
GameObject* soundIcon;
GameObject* muteIcon;*/
OptionsMenu::OptionsMenu(Scene* scene) : GameObject(scene, nullptr) {
  const auto panel =
      new GameObject(scene_, TextureManager::get("UI-WhiteBox"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 4),
                                   static_cast<int>(WIN_HEIGHT / 3)));
  const auto returnButton = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 1.65),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 10),
                    static_cast<int>(WIN_HEIGHT / 8)),
      [this]() { destroy(); }, "Return", "ButtonFont");
  GameObject* soundIcon = new GameObject(scene_, TextureManager::get("UI-ActiveSound"),
                             Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2.25),
                             Vector2D<int>(static_cast<int>(WIN_WIDTH / 25),
                                           static_cast<int>(WIN_HEIGHT / 20)));
  GameObject* muteIcon = new GameObject(scene_, TextureManager::get("UI-MuteSound"),
                            Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2.25),
                            Vector2D<int>(static_cast<int>(WIN_WIDTH / 25),
                                          static_cast<int>(WIN_HEIGHT / 20)));
  GameObject* greenTick =
      new GameObject(scene_, TextureManager::get("UI-greenTick"),
                     Vector2D<int>(WIN_WIDTH / 2.20, WIN_HEIGHT / 1.95),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 17),
                                   static_cast<int>(WIN_HEIGHT / 12)));
  greenTick->setTransparent(true);
  greenTick->setRenderizable(SDLAudioManager::getInstance()->getDefault());

  muteIcon->setRenderizable(SDLAudioManager::getInstance()->getMusicVolume() == 0);
  soundIcon->setRenderizable(SDLAudioManager::getInstance()->getMusicVolume() != 0);

  
  const auto moreSoundBox = new Button(
      scene_, TextureManager::get("Quantity-Button"),
      Vector2D<int>(WIN_WIDTH / 1.75, WIN_HEIGHT / 2.25),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 15),
                    static_cast<int>(WIN_HEIGHT / 8)),
      [this, muteIcon, soundIcon]() {
        const auto manager = SDLAudioManager::getInstance();
        if (!manager->getDefault() && manager->getMusicVolume() < 100) {
          manager->setChannelVolume(manager->getChannelVolume() + 10, 0);
          manager->setChannelVolume(manager->getChannelVolume() + 10, 1);
          manager->setMusicVolume(manager->getMusicVolume() + 10);

		  muteIcon->setRenderizable(manager->getMusicVolume() == 0);
          soundIcon->setRenderizable(manager->getMusicVolume() != 0);
        };
      },
      "+", "StatsFont");
  const auto LessSoundBox = new Button(
      scene_, TextureManager::get("Quantity-Button"),
      Vector2D<int>(WIN_WIDTH / 2.35, WIN_HEIGHT / 2.25),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 15),
                    static_cast<int>(WIN_HEIGHT / 8)),
      [this, muteIcon, soundIcon]() {
        const auto manager = SDLAudioManager::getInstance();
        if (!manager->getDefault() && manager->getMusicVolume() > 0) {
          manager->setChannelVolume(manager->getChannelVolume() - 10, 0);
          manager->setChannelVolume(manager->getChannelVolume() - 10, 1);
          manager->setMusicVolume(manager->getMusicVolume() - 10);

		  muteIcon->setRenderizable(manager->getMusicVolume() == 0);
          soundIcon->setRenderizable(manager->getMusicVolume() != 0);
        };
      },
      "-", "StatsFont");

  const auto DefaultText =
      new Text(scene_, FontManager::get("StatsFont"),
               Vector2D<int>(WIN_WIDTH / 1.9, WIN_HEIGHT / 1.9), {0, 0, 0, 0},
               "Default", 10000);
  const auto defaultButton = new Button(
      scene_, TextureManager::get("UI-cellFrame"),
      Vector2D<int>(WIN_WIDTH / 2.25, WIN_HEIGHT / 1.9),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 35),
                    static_cast<int>(WIN_WIDTH / 35)),
      [this, greenTick]() {
        const auto manager = SDLAudioManager::getInstance();
        manager->setDefault(!manager->getDefault());
        greenTick->setRenderizable(manager->getDefault());
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


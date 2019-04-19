// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "OptionsMenu.h"

#include "GameObjects/Button.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/TextureManager.h"
#include "Scenes/MenuScene.h"
#include "Structures/Game.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"
OptionsMenu::OptionsMenu(Scene* scene) : GameObject(scene, nullptr) {
  const auto panel =
      new GameObject(scene_, TextureManager::get("UI-OptionsMenu"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 4.68),
                                   static_cast<int>(WIN_HEIGHT / 2.25)));
  const auto returnButton =
      new Button(scene_, TextureManager::get("Button-Exit"),
                 Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 1.85),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 10),
                               static_cast<int>(WIN_HEIGHT / 12)),
                 [this]() { destroy(); });
  const auto noSoundButton =
      new Button(scene_, TextureManager::get("Button-Exit"),
                 Vector2D<int>(WIN_WIDTH / 1.5, WIN_HEIGHT / 1.85),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 10),
                               static_cast<int>(WIN_HEIGHT / 12)),
                 [this]() {
                   SDLAudioManager::getInstance()->setChannelVolume(0, 0);
                   SDLAudioManager::getInstance()->setMusicVolume(0);
                 });

  addChild(panel);
  addChild(returnButton);
  addChild(noSoundButton);
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "OptionsMenu.h"

#include "GameObjects/Button.h"
#include "Managers/FontManager.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/TextureManager.h"
#include "Scenes/MenuScene.h"
#include "Structures/Game.h"
#include "Text.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"
OptionsMenu::OptionsMenu(Scene* scene) : GameObject(scene, nullptr) {
  const auto panel =
      new GameObject(scene_, TextureManager::get("UI-OptionsMenu"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 4.5),
                                   static_cast<int>(WIN_HEIGHT / 2)));
  const auto returnButton =
      new Button(scene_, TextureManager::get("Button-Exit"),
                 Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 1.85),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 14),
                               static_cast<int>(WIN_HEIGHT / 12)),
                 [this]() { destroy(); });
  const auto noSoundButton =
      new Button(scene_, TextureManager::get("UI-ActiveSound"),
                 Vector2D<int>(WIN_WIDTH / 1.85, WIN_HEIGHT / 2.15),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 24),
                               static_cast<int>(WIN_HEIGHT / 20)),
                 [this]() { SDLAudioManager::getInstance()->setMute(false); });
  const auto soundButton =
      new Button(scene_, TextureManager::get("UI-MuteSound"),
                 Vector2D<int>(WIN_WIDTH / 2.15, WIN_HEIGHT / 2.15),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 22),
                               static_cast<int>(WIN_HEIGHT / 20)),
                 [this]() { SDLAudioManager::getInstance()->setMute(true); });

  addChild(panel);
  addChild(returnButton);
  addChild(noSoundButton);
  addChild(soundButton);
}

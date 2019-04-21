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
void highervolume() {
  SDLAudioManager::getInstance()->setChannelVolume(
      SDLAudioManager::getInstance()->getChannelVolume() + 10, 0);
  SDLAudioManager::getInstance()->setChannelVolume(
      SDLAudioManager::getInstance()->getChannelVolume() + 10, 1);
  SDLAudioManager::getInstance()->setMusicVolume(
      SDLAudioManager::getInstance()->getMusicVolume() + 10);
}
void lowervolume() {
  SDLAudioManager::getInstance()->setChannelVolume(
      SDLAudioManager::getInstance()->getChannelVolume() - 10, 0);
  SDLAudioManager::getInstance()->setChannelVolume(
      SDLAudioManager::getInstance()->getChannelVolume() - 10, 1);
  SDLAudioManager::getInstance()->setMusicVolume(
      SDLAudioManager::getInstance()->getMusicVolume() - 10);
}
OptionsMenu::OptionsMenu(Scene* scene) : GameObject(scene, nullptr) {
  const auto panel =
      new GameObject(scene_, TextureManager::get("Pause-Background"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 4),
                                   static_cast<int>(WIN_HEIGHT / 3)));
  const auto returnButton =
      new Button(scene_, TextureManager::get("Button-Exit"),
                 Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 1.65),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 14),
                               static_cast<int>(WIN_HEIGHT / 12)),
                 [this]() { destroy(); });
  /* const auto noSoundButton =
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
                  [this]() { SDLAudioManager::getInstance()->setMute(true);
   });*/
  const auto moreSoundBox =
      new Button(scene_, TextureManager::get("Quantity-Button"),
                 Vector2D<int>(WIN_WIDTH / 2.3, WIN_HEIGHT / 2.15),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 18),
                               static_cast<int>(WIN_HEIGHT / 10)),
                 [this]() { highervolume(); });
  const auto LessSoundBox =
      new Button(scene_, TextureManager::get("Quantity-Button"),
                 Vector2D<int>(WIN_WIDTH / 1.75, WIN_HEIGHT / 2.15),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 18),
                               static_cast<int>(WIN_HEIGHT / 10)),
                 [this]() { lowervolume(); });

  const auto plusText =
      new Text(scene_, FontManager::get("StatsFont"),
               Vector2D<int>(WIN_WIDTH / 1.75, WIN_HEIGHT / 2.15), {0, 0, 0, 0},
               " mas dd", 10000);
  const auto minusText =
      new Text(scene_, FontManager::get("Retron2000"),
               Vector2D<int>(WIN_WIDTH / 1.75, WIN_HEIGHT / 2.15), {0, 0, 0, 0},
               "-", 10000);

  addChild(panel);
  scene_->addGameObject(plusText);
  addChild(returnButton);
  addChild(moreSoundBox);
  addChild(LessSoundBox);

  // addChild(noSoundButton);
  // addChild(soundButton);
}

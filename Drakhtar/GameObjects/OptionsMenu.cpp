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
GameObject* greenTick = nullptr;
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
      new GameObject(scene_, TextureManager::get("UI-WhiteBox"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 4),
                                   static_cast<int>(WIN_HEIGHT / 3)));
  const auto returnButton =
      new Button(scene_, TextureManager::get("Button-Exit"),
                 Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 1.65),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 14),
                               static_cast<int>(WIN_HEIGHT / 12)),
                 [this]() { destroy(); });
  const auto soundIcon =
      new GameObject(scene_, TextureManager::get("UI-ActiveSound"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2.25),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 22),
                                   static_cast<int>(WIN_HEIGHT / 20)));
  const auto moreSoundBox = new Button(
      scene_, TextureManager::get("Quantity-Button"),
      Vector2D<int>(WIN_WIDTH / 1.75, WIN_HEIGHT / 2.25),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 15),
                    static_cast<int>(WIN_HEIGHT / 8)),
      [this]() {
        SDLAudioManager::getInstance()->getDefault() ? NULL : highervolume();
      });
  const auto LessSoundBox = new Button(
      scene_, TextureManager::get("Quantity-Button"),
      Vector2D<int>(WIN_WIDTH / 2.35, WIN_HEIGHT / 2.25),
      Vector2D<int>(static_cast<int>(WIN_WIDTH / 15),
                    static_cast<int>(WIN_HEIGHT / 8)),
      [this]() {
        SDLAudioManager::getInstance()->getDefault() ? NULL : lowervolume();
      });

  const auto plusText =
      new Text(scene_, FontManager::get("StatsFont"),
               Vector2D<int>(WIN_WIDTH / 1.75, WIN_HEIGHT / 2.26), {0, 0, 0, 0},
               "+", 10000);
  const auto minusText =
      new Text(scene_, FontManager::get("StatsFont"),
               Vector2D<int>(WIN_WIDTH / 2.35, WIN_HEIGHT / 2.26), {0, 0, 0, 0},
               "-", 10000);
  const auto DefaultText =
      new Text(scene_, FontManager::get("StatsFont"),
               Vector2D<int>(WIN_WIDTH / 1.9, WIN_HEIGHT / 1.9), {0, 0, 0, 0},
               "Default", 10000);
  greenTick = new GameObject(scene_, TextureManager::get("UI-greenTick"),
                             Vector2D<int>(WIN_WIDTH / 2.20, WIN_HEIGHT / 1.95),
                             Vector2D<int>(static_cast<int>(WIN_WIDTH / 17),
                                           static_cast<int>(WIN_HEIGHT / 12)));
  greenTick->setTransparent(true);
  const auto defaultButton =
      new Button(scene_, TextureManager::get("UI-cellFrame"),
                 Vector2D<int>(WIN_WIDTH / 2.25, WIN_HEIGHT / 1.9),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 35),
                               static_cast<int>(WIN_WIDTH / 35)),
                 [this]() {
                   SDLAudioManager::getInstance()->setDefault(
                       !SDLAudioManager::getInstance()->getDefault());
                 });

  addChild(panel);
  moreSoundBox->addChild(plusText);
  LessSoundBox->addChild(minusText);
  addChild(returnButton);
  addChild(moreSoundBox);
  addChild(LessSoundBox);
  addChild(soundIcon);
  addChild(DefaultText);
  addChild(defaultButton);
  // addChild(greenTick);
}

OptionsMenu::~OptionsMenu() {
  delete greenTick;
  greenTick = nullptr;
}

void OptionsMenu::render() const {
  GameObject::render();
  if (SDLAudioManager::getInstance()->getDefault()) {
    greenTick->render(greenTick->getRect());
  }
}

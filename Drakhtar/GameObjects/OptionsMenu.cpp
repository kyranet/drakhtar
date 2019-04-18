// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "OptionsMenu.h"

#include "Managers/SDLAudioManager.h"
#include "Managers/TextureManager.h"
#include "Scenes/MenuScene.h"
#include "Utils/Constants.h"
#include "Utils/Vector2D.h"
OptionsMenu::OptionsMenu(Scene* scene) : GameObject(scene, nullptr) {
  const auto panel =
      new GameObject(scene_, TextureManager::get("Pause-Panel"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(static_cast<int>(WIN_WIDTH / 4.68),
                                   static_cast<int>(WIN_HEIGHT / 2.25)));

  addChild(panel);
}

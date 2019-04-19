// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "ButtonText.h"
#include "Text.h"
#include "../Structures/Font.h"
#include "Managers/FontManager.h"
#include <utility>
#include "Utils/Constants.h"

ButtonText::ButtonText(Scene* scene, const std::string& text,
                       const std::string& fontFile, const SDL_Rect buttonArea,
                       int posX, int posY)
    : GameObject(scene, nullptr, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                 Vector2D<int>(1, 1)) {
  spriteText_ = text;

    const auto lineJumpLimit = static_cast<int>(buttonArea.w * 1.25);

  const SDL_Color textColor = {225, 225, 225, 255};

  const auto buttonText_ =
      new Text(scene, FontManager::get(fontFile), Vector2D<int>(1, 1),
               textColor, spriteText_, 1);

  buttonText_->setColor(textColor);
  buttonText_->setText(spriteText_, textColor, lineJumpLimit);
  buttonText_->setSize(Vector2D<int>(buttonArea.x/5 + buttonArea.h / 20,
                                     buttonArea.y/5 - buttonArea.w / 20));
  buttonText_->setPosition(Vector2D<int>(posX, posY));

  addChild(buttonText_);
}

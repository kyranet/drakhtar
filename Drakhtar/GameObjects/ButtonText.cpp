// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "ButtonText.h"
#include "Text.h"
#include "../Structures/Font.h"
#include "Managers/FontManager.h"
#include <utility>
#include "Utils/Constants.h"

ButtonText::ButtonText(Scene* scene, const std::string& text,
                       const std::string& fontFile, Vector2D<int>(size),
                       Vector2D<int>(pos))
    : GameObject(scene, nullptr, pos, size) {
  spriteText_ = text;

  const auto lineJumpLimit = static_cast<int>(size.getX() * 1.5);

  const SDL_Color textColor = {225, 225, 225, 255};

  const auto buttonText_ =
      new Text(scene, FontManager::get(fontFile), Vector2D<int>(1, 1),
               textColor, spriteText_, 1);

  buttonText_->setColor(textColor);
  buttonText_->setSize(Vector2D<int>(size.getX() + WIN_HEIGHT / 1.48,
                                     size.getY() - WIN_WIDTH / 5.45));
  buttonText_->setPosition(pos);
  buttonText_->setText(spriteText_, textColor, lineJumpLimit);

  addChild(buttonText_);
}

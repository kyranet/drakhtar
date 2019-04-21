// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "ButtonText.h"

#include <utility>

#include "../Structures/Font.h"
#include "Managers/FontManager.h"
#include "Text.h"
#include "Utils/Constants.h"

ButtonText::ButtonText(Scene* scene, const std::string& text,
                       const std::string& fontFile, Vector2D<int>(size),
                       Vector2D<int>(pos))
    : GameObject(scene, nullptr, pos, size) {
  const auto lineJumpLimit = static_cast<int>(size.getX() * 1.5);

  const SDL_Color textColor = {225, 225, 225, 255};

  const auto buttonText = new Text(scene, FontManager::get(fontFile),
                                   Vector2D<int>(1, 1), textColor, text, 1);

  buttonText->setColor(textColor);
  buttonText->setSize(
      {static_cast<int>(floor(size.getX() + WIN_HEIGHT / 1.48)),
       static_cast<int>(floor(size.getY() - WIN_WIDTH / 5.45))});
  buttonText->setPosition(pos);
  buttonText->setText(text, textColor, lineJumpLimit);
  buttonText->setTransparent(true);

  addChild(buttonText);
}

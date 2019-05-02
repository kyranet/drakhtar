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
    : GameObject(scene, nullptr, pos, size), fontFile_(fontFile) {
  lineJumpLimit = static_cast<int>(size.getX() * 1.5);

  textColor = {225, 225, 225, 255};

  const auto text_ = new Text(scene, FontManager::get(fontFile),
                              Vector2D<int>(1, 1), textColor, text, 1);

  text_->setColor(textColor);
  text_->setSize({static_cast<int>(floor(size.getX() + WIN_HEIGHT / 1.48)),
                  static_cast<int>(floor(size.getY() - WIN_WIDTH / 5.45))});
  text_->setPosition(pos);
  text_->setText(text, textColor, lineJumpLimit);
  text_->setTransparent(true);

  addChild(text_);
}

void ButtonText::setText(std::string text) {
  delete children_[0];
  removeChild(children_[0]);
  const auto text_ = new Text(getScene(), FontManager::get(fontFile_),
                              Vector2D<int>(1, 1), textColor, text, 1);
  text_->setColor(textColor);
  text_->setSize(
      {static_cast<int>(floor(getSize().getX() + WIN_HEIGHT / 1.48)),
       static_cast<int>(floor(getSize().getY() - WIN_WIDTH / 5.45))});
  text_->setPosition(getPosition());
  text_->setText(text, textColor, lineJumpLimit);
  text_->setTransparent(true);

  addChild(text_);
}

void ButtonText::setColor(const SDL_Color& color) {
  reinterpret_cast<Text*>(children_[0])->setColor(color);
}

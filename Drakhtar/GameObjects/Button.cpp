// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Button.h"
#include <utility>
#include "Managers/Input.h"
#include "Text.h"
#include "../Structures/Font.h"
#include "Managers/FontManager.h"

Button::Button(Scene* scene, Texture* texture, const Vector2D<int>& pos,
               const Vector2D<int>& size, std::function<void()> callback,
               const std::string& text, const std::string& fontFile)
    : GameObject(scene, texture, pos, size), callback_(std::move(callback)) {
  spriteText_ = text;

  const SDL_Color textColor = {0, 0, 0, 255};

  const auto buttonText_ = new Text(
      scene, FontManager::get(fontFile),
      Vector2D<int>(size.getX() + pos.getX(), size.getY() - pos.getY()),
      textColor, spriteText_, 2);

  buttonText_->setColor(textColor);
  buttonText_->setText(spriteText_, textColor, 2);

  addChild(buttonText_);
}

void Button::update() {
  GameObject::update();

  if (Input::isMouseButtonDown(MouseKey::LEFT) &&
      reinterpret_cast<Button*>(Input::screenMouseToRay()) == this) {
    callback_();
  }
}

void Button::render() const { GameObject::render(); }

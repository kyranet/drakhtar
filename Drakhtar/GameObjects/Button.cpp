// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Button.h"

#include <utility>

#include "../Structures/Font.h"
#include "Managers/FontManager.h"
#include "Managers/Input.h"
#include "Text.h"

Button::Button(Scene* scene, Texture* texture, const Vector2D<int>& pos,
               const Vector2D<int>& size, std::function<void()> callback,
               const std::string& text, const std::string& fontFile)
    : GameObject(scene, texture, pos, size), callback_(std::move(callback)) {
  spriteText_ = text;

  const SDL_Color textColor = {225, 225, 225, 255};

  const auto buttonText_ =
      new Text(scene, FontManager::get(fontFile),
               Vector2D<int>(pos.getX() + WIN_WIDTH / 20,
                             this->getRect().y + WIN_HEIGHT / 200),
               textColor, spriteText_, this->getRect().w * 0.95);

  buttonText_->setColor(textColor);
  buttonText_->setText(spriteText_, textColor, this->getRect().w * 0.95);
  buttonText_->setPosition(Vector2D<int>(pos.getX(), pos.getY()));
  buttonText_->setSize(Vector2D<int>(size.getX()*0.65, size.getY()*0.8));

  addChild(buttonText_);
}

void Button::update() {
  GameObject::update();

  if ((Input::isMouseButtonDown(MouseKey::LEFT) ||
       Input::isMouseButtonDown(MouseKey::RIGHT)) &&
      reinterpret_cast<Button*>(Input::screenMouseToRay()) == this) {
    callback_();
  }
}

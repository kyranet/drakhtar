// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Button.h"
#include <utility>
#include "Managers/Input.h"

Button::Button(Scene* scene, Texture* texture, const Vector2D<int>& pos,
               const Vector2D<int>& size, std::function<void()> callback,
               const std::string& text, const std::string& fontFile)
    : GameObject(scene, texture, pos, size), callback_(std::move(callback)) {
  const auto buttonText_ =
      new ButtonText(scene, text, fontFile, size, pos);

  addChild(buttonText_);
}

void Button::update() {
  GameObject::update();

  if ((Input::isMouseButtonDown(MouseKey::LEFT) ||
       Input::isMouseButtonDown(MouseKey::RIGHT)) &&
      (reinterpret_cast<Button*>(Input::screenMouseToRay()) == this ||
       reinterpret_cast<Button*>(Input::isMouseInside(&this->getRect())))) {
    callback_();
  }
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Button.h"

#include <utility>

#include "EventListeners/ButtonListener.h"
#include "Managers/Input.h"

Button::Button(Scene* scene, Texture* texture, const Vector2D<int>& pos,
               const Vector2D<int>& size, std::function<void()> callback,
               const std::string& text, const std::string& fontFile)
    : GameObject(scene, texture, pos, size), callback_(std::move(callback)) {
  // Create the text
  const auto buttonText = new ButtonText(scene, text, fontFile, size, pos);
  buttonText->setTransparent(true);

  addChild(buttonText);
  addEventListener(new ButtonListener(this));
}

void Button::call() { callback_(); }

void Button::render() const {
  if (hovered_) {
    GameObject::render({position_.getX(), position_.getY(), size_.getX() + 5,
                        size_.getY() + 5});
  } else {
    GameObject::render(getRect());
  }
}

void Button::update() {
  const auto area = getRect();
  hovered_ = Input::isMouseInside(&area);
  GameObject::update();
}

SDL_Rect Button::getRect() const {
  return {position_.getX(), position_.getY(), size_.getX(), size_.getY()};
}

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
  increSize_ = 15;

  addChild(buttonText);
  addEventListener(new ButtonListener(this));
}

void Button::call() { callback_(); }

void Button::render() const {
  if (hovered_) {
    GameObject::render(changeRect());
  } else {
    GameObject::render(getRect());
  }
}

void Button::update() {
  const auto area = getRect();
  hovered_ = Input::isMouseInside(&area);
  GameObject::update();
}

void Button::setColor(const SDL_Color& color) {
  reinterpret_cast<ButtonText*>(children_[0])->setColor(color);
}

SDL_Rect Button::getRect() const {
  return {position_.getX() - size_.getX() / 2,
          position_.getY() - size_.getY() / 2, size_.getX(), size_.getY()};
}

SDL_Rect Button::changeRect() const {
  return {position_.getX() - (size_.getX() + increSize_) / 2,
          position_.getY() - (size_.getY() + increSize_) / 2,
          size_.getX() + increSize_, size_.getY() + increSize_};
}

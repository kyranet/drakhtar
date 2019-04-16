// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Button.h"

#include <utility>

#include "Managers/Input.h"

Button::Button(Scene* scene, Texture* texture, const Vector2D<int>& pos,
               const Vector2D<int>& size, std::function<void()> callback)
    : GameObject(scene, texture, pos, size), callback_(std::move(callback)) {}

void Button::update() {
  GameObject::update();

  if (Input::isMouseButtonDown(MouseKey::LEFT) &&
      reinterpret_cast<Button*>(Input::screenMouseToRay()) == this) {
    callback_();
  }
}

void Button::handleEvents(SDL_Event e) {
  if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
    SDL_Point p = {e.button.x, e.button.y};
    const auto area = getRect();
    if (SDL_PointInRect(&p, &area)) {
      callback_();
    }
  }
}

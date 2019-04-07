// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Button.h"

Button::Button(Scene* scene, Texture* texture, const Vector2D<int>& pos,
               const Vector2D<int>& size, const Callback callback)
    : GameObject(scene, texture, pos, size), callback_(callback) {}

void Button::handleEvents(const SDL_Event e) {
  // Only handle when it's a left click
  if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
    SDL_Point p = {e.button.x, e.button.y};
    const auto area = getRect();
    if (SDL_PointInRect(&p, &area)) {
      callback_();
    }
  }
}

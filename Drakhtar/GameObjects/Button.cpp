// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Button.h"

Button::Button(Scene *scene, Texture *texture, Vector2D<int> pos,
               Vector2D<int> size, Callback *callback)
    : GameObject(scene, texture, pos, size), callback_(callback) {}

void Button::handleEvents(SDL_Event e) {
  // Only handle when it's a left click
  if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
    SDL_Point p = {e.button.x, e.button.y};
    if (SDL_PointInRect(&p, &getRect())) {
      callback_();
    }
  }
}

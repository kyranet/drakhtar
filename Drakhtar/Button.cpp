// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Button.h"

Button::Button(Texture *t, int x, int y, int w, int h,
               void (*callback)(Game *game, SDL_Renderer *renderer), Game *game, SDL_Renderer *renderer)
    : GameObject(t, Vector2D<int>(x, y), Vector2D<int>(w, h)),
      texture(t),
      x(x), y(y),
      w(w), h(h),
      cb(callback),
      game(game),
      renderer(renderer) {}

Button::Button(Texture *t, int x, int y, int w, int h,
               void (*callback)(SDL_Renderer *renderer), SDL_Renderer *renderer)
    : GameObject(t, Vector2D<int>(x, y), Vector2D<int>(w, h)),
      texture(t),
      x(x), y(y),
      w(w), h(h),
      cbPause(callback),
      renderer(renderer)
{
}

void Button::handleEvents(SDL_Event e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
    {
        // RATON IZQUIERDO
        SDL_Point p = {e.button.x, e.button.y};
        SDL_Rect r = {x - (w / 2), y - (h / 2), w, h};
        if (SDL_PointInRect(&p, &r))
        {
            cb(game, renderer);
        }
    }
}

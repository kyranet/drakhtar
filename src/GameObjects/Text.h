// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <iostream>

#include "GameObject.h"
#include "SDL.h"

class Font;
class Scene;

class Text : public GameObject {
  Font* font_;
  std::string text_;
  SDL_Color color_;

 public:
  Text(Scene* scene, Font* font, Vector2D<int> position, SDL_Color color,
       const std::string& text, int lineJumpLimit);
  ~Text();
  void setText(const std::string& text, const SDL_Color& color = {0, 0, 0, 255},
               int lineJumpLimit = 250);
  void setColor(const SDL_Color& color);
  void render() const override;
  void render(SDL_Rect rect) const override;
};

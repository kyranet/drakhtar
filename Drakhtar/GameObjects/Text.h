// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <iostream>
#include "GameObject.h"
#include "SDL.h"

class Font;
class Scene;

class Text : public GameObject {
 private:
  Font *font_;
  std::string text_;
  SDL_Color color_;

 public:
  Text(Scene *scene, Font *font, Vector2D<int> position, SDL_Color color,
       std::string text, int lineJumpLimit);
  ~Text();
  void setText(std::string const text, SDL_Color const color = {0, 0, 0, 255},
               int lineJumpLimit = 250);
  void setColor(SDL_Color const color);
  void render() const;
};

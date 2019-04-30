// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"

class Text;
class Font;
class Scene;
class TutorialSequence;

class ButtonText : public GameObject {
  SDL_Color textColor;
  int lineJumpLimit;
  std::string fontFile_;

 public:
  ButtonText(Scene* scene, const std::string& text, const std::string& fontFile,
             Vector2D<int>(size), Vector2D<int>(pos));

  void setText(std::string text);
  void setColor(const SDL_Color& color);
};

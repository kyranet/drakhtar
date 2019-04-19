// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <functional>
#include <fstream>
#include "../EventListeners/ListenerOnClick.h"
#include "GameObject.h"
#include "SDL.h"

class Text;
class Font;
class Scene;
class TutorialSequence;

class ButtonText : public GameObject {
  std::string buttonText_;
  std::string spriteText_;

 public:
  ButtonText(Scene* scene, const std::string& text, const std::string& fontFile,
             const SDL_Rect buttonArea, int posX, int posY);
};

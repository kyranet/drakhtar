// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"

class Text;
class Font;
class Scene;

class Dialog : public GameObject {
  std::string characterName_;
  std::string spriteText_;
  std::string dialogText_;
  SDL_Rect dialogueArea_;
public:
  Dialog(Scene* scene, std::ifstream& file, Font* textFont, SDL_Rect dialogRect,
         int lineJumpLimit);
  void readFromFile(std::ifstream& file);
};

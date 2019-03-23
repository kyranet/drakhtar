// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <fstream>
#include <iostream>
#include "GameObject.h"

class Text;
class Font;
class Scene;

class Dialog : public GameObject {
 private:
  std::string characterName;
  std::string spriteText;
  std::string dialogText;

  GameObject* characterPortraitSprite = nullptr;
  Text* characterNameSprite = nullptr;
  Text* dialogTextSprite = nullptr;

  SDL_Rect dialogRect_;

 public:
  Dialog(Scene *scene, std::ifstream& file, Font* textfont, SDL_Rect dialogRect,
         int lineJumpLimit);
  ~Dialog();
  virtual void render() const;
  void readFromFile(std::ifstream& file);
};

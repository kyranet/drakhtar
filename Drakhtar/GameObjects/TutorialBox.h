// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../EventListeners/ListenerOnClick.h"
#include "GameObject.h"
#include <fstream>

class Text;
class Font;
class Scene;
class TutorialSequence;

class TutorialBox : public GameObject {
  std::string imageText_;
  std::string dialogText_;
  std::string renderizable;
  int posX, posY;

 public:
  TutorialBox(Scene *scene, std::ifstream &file, Font *textFont);
  void readFromFile(std::ifstream &file);
  bool getVisible();
};

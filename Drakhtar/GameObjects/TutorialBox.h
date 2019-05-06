// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <fstream>
#include "../EventListeners/ListenerOnClick.h"
#include "GameObject.h"

class Text;
class Font;
class Scene;
class TutorialSequence;
class TutorialText;

class TutorialBox : public GameObject {
  std::string imageText_;
  std::string dialogText_;
  std::string renderizable;

  TutorialText* tutorialText_ = nullptr;
  ;
  int posX, posY;

 public:
  TutorialBox(Scene* scene,  std::string& filename);
};

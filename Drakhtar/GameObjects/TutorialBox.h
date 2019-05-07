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

  //TutorialText* tutorialText_ = nullptr;

 public:
  TutorialBox(Scene* scene, std::string& filename, Vector2D<int> pos,
              Vector2D<int> size);
  void setBoxPosition(Vector2D<int> pos);
  void setNextButtonRender(bool next);
  void setCloseButtonRender(bool close);
};

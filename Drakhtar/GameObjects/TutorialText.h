// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "EventListeners/StoreListener.h"
#include "GameObject.h"
#include "../Utils/Constants.h"
class Scene;
class Text;
class Font;
class TutorialBox;

class TutorialText : public GameObject {
  std::vector<TutorialTexts> texts;
 public:
  TutorialText(Scene* scene, TutorialBox* box,std::string& file);
  void render() const override;
  void readFromFile(std::string& filename);
};

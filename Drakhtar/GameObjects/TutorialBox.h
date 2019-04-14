// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <fstream>
#include "GameObject.h"

class Text;
class Font;
class Scene;
class TutorialSequence;

class TutorialBox : public GameObject {
  std::string imageText_;
  std::string dialogText_;

 public:
  TutorialBox(Scene *scene, std::ifstream &file, Font *textFont,
              SDL_Rect tutorialArea, SDL_Rect dialogueBackground);
  void readFromFile(std::ifstream &file);
};

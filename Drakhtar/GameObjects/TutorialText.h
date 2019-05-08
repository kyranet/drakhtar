// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../Utils/Constants.h"
#include "EventListeners/StoreListener.h"
#include "GameObject.h"
class Scene;
class Text;
class Font;
class TutorialBox;

class TutorialText : public GameObject {
  std::vector<TutorialTexts> texts;
  int cont = 0;
  Text* text = nullptr;

 public:
  TutorialText(Scene* scene, TutorialBox* box, std::string& file,
               SDL_Rect rect);
  ~TutorialText();
  void render() const override;
  void readFromFile(std::string& filename);
  bool addCount();
  bool getClosed(int x);
  int getCont() const;
};

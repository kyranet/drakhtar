// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../Utils/Constants.h"
#include "EventListeners/StoreListener.h"
#include "GameObject.h"
class Scene;
class Text;
class Font;
class TutorialBox;

class TutorialText final : public GameObject {
  std::vector<std::string> texts;
  unsigned int cont = 0;
  Text* text_ = nullptr;

 public:
  TutorialText(Scene* scene, SDL_Rect rect);
  ~TutorialText();
  void render() const override;
  void readFromLocale();
  bool addCount();
  bool getClosed(int x);
  int getCont() const;
};

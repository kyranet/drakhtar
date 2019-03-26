// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "../EventListeners/ListenerOnClick.h"
#include "GameObject.h"

class Dialog;
class Scene;
class Font;

class DialogScene : public GameObject {
 private:
  std::vector<Dialog*> dialogues;
  int dialogueIndex = 0;
  int lineJumpLimit_ = 0;
  void readFromFile(std::string filename, Font* textFont, SDL_Rect rect);

 public:
  DialogScene(Scene* scene, std::string filename, std::string fontfile);
  ~DialogScene();
  void next();
  virtual void render() const;
};

class DialogSceneOnClick : public ListenerOnClick {
 public:
  DialogSceneOnClick::DialogSceneOnClick(GameObject* gameObject)
      : ListenerOnClick(gameObject) {}
  void onClickStop(SDL_Point point);
};

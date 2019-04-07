
// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../EventListeners/ListenerOnClick.h"
#include "GameObject.h"
#include <fstream>
#include <iostream>
#include <queue>

class TutorialBox;
class Scene;
class Font;

class TutorialSequence : public GameObject {
private:
  std::queue<TutorialBox *> tutorials;
  TutorialBox *currentTutorial = nullptr;
  void readFromFile(const std::string &filename, Font *textFont, SDL_Rect tutorialArea, SDL_Rect dialogueBackground);
  static TutorialSequence *instance_;
public:
  TutorialSequence(Scene *scene, const std::string &filename,
                   const std::string &fontfile);
  ~TutorialSequence();
  void createNextTutorial();
  virtual void render() const;
};

class TutorialSceneOnClick : public ListenerOnClick {
public:
	TutorialSceneOnClick::TutorialSceneOnClick(GameObject *gameObject)
		: ListenerOnClick(gameObject) {}
	void onClickStop(SDL_Point point);
};

#pragma once

#include "../EventListeners/ListenerOnClick.h"
#include "GameObject.h"
#include <fstream>
#include <iostream>
#include <vector>

class Text;
class Font;
class Scene;
class TutorialSequence;

class TutorialBox : public GameObject {
private:
  std::string imageText_;
  std::string dialogText_;

public:
  TutorialBox(Scene *scene, std::ifstream &file, Font *textfont, SDL_Rect tutorialArea, SDL_Rect dialogueBackground);
  void readFromFile(std::ifstream &file);
};

/*class TutorialSceneOnClick : public ListenerOnClick {
public:
	TutorialSceneOnClick::TutorialSceneOnClick(GameObject *gameObject)
		: ListenerOnClick(gameObject) {}
	void onClickStop(SDL_Point point);
};*/
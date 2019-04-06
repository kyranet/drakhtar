#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include "../EventListeners/ListenerOnClick.h"
#include "GameObject.h"

class Text;
class Font;
class Scene;

class TutorialBox : public GameObject {
private:
	std::string imageText_;
	std::string dialogText_;

public:
	TutorialBox(Scene* scene, std::ifstream& file, Font* textfont, int lineJumpLimit);
	void readFromFile(std::ifstream& file);
	

};

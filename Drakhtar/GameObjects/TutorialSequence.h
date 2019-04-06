
// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <fstream>
#include <iostream>
#include <stack>
#include "../EventListeners/ListenerOnClick.h"
#include "GameObject.h"

class TutorialBox;
class Scene;
class Font;

class TutorialSequence : public GameObject
{
private:
	std::stack<TutorialBox*> tutorials;
	TutorialBox* currentTutorial = nullptr;
	int lineJumpLimit;
	void readFromFile(const std::string &filename, Font *textFont);

public:
	TutorialSequence(Scene *scene, const std::string &filename, const std::string &fontfile);
	~TutorialSequence();
	void createNextTutorial();
	virtual void render() const;
};

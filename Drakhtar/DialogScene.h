#pragma once

#include "State.h"
#include "Dialog.h"
#include <iostream>
#include <vector>

class DialogScene
{
private:
	int dialogChainSize = 0;
	vector<Dialog*> dialogChain;
	int currentDialogIndex = 0;
public:
	DialogScene(int dialogSize);
	~DialogScene();
	void render();
	void handleEvents(SDL_Event event);
	void readFromFile();
	void nextDialog();
	void endOfDialog();

};


#pragma once

#include "State.h"
#include "Dialog.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <fstream>

class DialogScene
{
private:
	GameObject* dialogBlockSprite = nullptr;
	int dialogChainSize = 0;
	vector<Dialog*> dialogChain;
	int currentDialogIndex = 0;
	Font* textFont = nullptr;
public:
	DialogScene(Game* game, string filename, string fontfile);
	~DialogScene();
	void render();
	void handleEvents(SDL_Event event);
	void readFromFile(Game* game, string filename, Font* textFont);
	void nextDialog();
	void endOfDialog();

};


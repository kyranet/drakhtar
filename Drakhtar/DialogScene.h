#pragma once

#include "Dialog.h"
#include "Font.h"
#include <iostream>
#include <vector>
#include <fstream>

class Game;
class Dialog;

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


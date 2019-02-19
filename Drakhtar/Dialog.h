#pragma once

#include "GameObject.h"
#include "Text.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include "checkML.h"

class Game;

class Dialog
{
private:
	string characterName;
	int spriteText;
	string dialogText;

	GameObject* characterPortraitSprite = nullptr;
	Text* characterNameSprite = nullptr;
	Text* dialogTextSprite = nullptr;
public:
	Dialog(Game* game, ifstream& file, Font* textfont);
	~Dialog();
	virtual void render() const;
	void readFromFile(ifstream& file);
};


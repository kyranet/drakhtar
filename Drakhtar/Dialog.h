#pragma once

#include "GameObject.h"
#include "Text.h"
#include "Game.h"
#include <iostream>
#include <fstream>


class Dialog
{
private:
	string characterName;
	string spriteText;
	string dialogText;

	GameObject* characterPortraitSprite = nullptr;
	Text* characterNameSprite = nullptr;
	Text* dialogTextSprite = nullptr;
public:
	Dialog(Game* game, ifstream& file);
	~Dialog();
	virtual void render() const;
	void readFromFile(ifstream& file);
};


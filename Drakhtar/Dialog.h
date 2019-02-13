#pragma once

#include "GameObject.h"
#include "Text.h"
#include <iostream>

class Dialog
{
private:
	string characterName;
	string dialogText;

	GameObject* dialogBlockSprite = nullptr;
	GameObject* characterPortraitSprite = nullptr;
	Text* characterNameSprite = nullptr;
	Text* dialogTextSprite = nullptr;
public:
	Dialog(string charName, string diagText);
	~Dialog();
	virtual void render() const;
	void readFromFile();
};


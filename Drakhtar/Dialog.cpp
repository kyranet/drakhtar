#include "Dialog.h"



Dialog::Dialog(Game* game, ifstream& file, Font* textFont)
{
	readFromFile(file);
	characterPortraitSprite = new GameObject(game->getTextures[spriteText] , vector2d{ 220, 350 }, vector2d{ 70, 70 });

	SDL_Color textColor;
	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;
	textColor.a = 1;

	characterNameSprite = new Text(textFont, vector2d{ 220, 370 }, vector2d{ 50, 50 }, textColor, characterName);
	dialogTextSprite = new Text(textFont, vector2d{ 400, 400 }, vector2d{ 50, 50 }, textColor, dialogText);
}


Dialog::~Dialog()
{
	delete characterPortraitSprite;
	characterPortraitSprite = nullptr;
	delete characterNameSprite;
	characterNameSprite = nullptr;
	delete dialogTextSprite;
	dialogTextSprite = nullptr;
}

void Dialog::render() const
{
	characterPortraitSprite->render();
	characterNameSprite->render();
	dialogTextSprite->render();
}

void Dialog::readFromFile(ifstream& file)
{
	file >> characterName;
	file >> spriteText;

	string text; // full dialog text
	string word = ""; // word added to text each iteration
	while (word != ".")
	{
		file >> word;
		if (word != ".")
			text += word + " ";
	}
	dialogText = text;
}

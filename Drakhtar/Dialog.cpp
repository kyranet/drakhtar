#include "Dialog.h"



Dialog::Dialog(Game* game, ifstream& file)
{
	readFromFile(file);
	characterPortraitSprite = new GameObject(game->getTextures[spriteText] , vector2d{ 220, 350 }, vector2d{ 70, 70 });
	//characterNameSprite = new Text(COGER FUENTE, vector2d{ 220, 370 }, vector2d{ 50, 50 }, COGER COLOR, characterName);
	//dialogTextSprite = new Text(COGER FUENTE, vector2d{ 400, 400 }, vector2d{ 50, 50 }, COGER COLOR, dialogText);
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

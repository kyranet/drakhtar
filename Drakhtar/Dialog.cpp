#include "Dialog.h"



Dialog::Dialog(Game* game, ifstream& file, Font* textFont)
{
	readFromFile(file);
	characterPortraitSprite = new GameObject(game->getTextures()[spriteText] , Vector2D<int>(200, 345), Vector2D<int>(150, 150));

	SDL_Color textColor;
	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;
	textColor.a = 1;

	int fontsize = textFont->getSize();

	characterNameSprite = new Text(game->getRenderer(), textFont, Vector2D<int>(600, 370), Vector2D<int>(fontsize*characterName.length(), 50), textColor, characterName);
	dialogTextSprite = new Text(game->getRenderer(), textFont, Vector2D<int>(110, 450), Vector2D<int>(fontsize*dialogText.length(), 20), textColor, dialogText);
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

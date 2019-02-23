#include "Dialog.h"



Dialog::Dialog(Game* game, ifstream& file, Font* textFont, SDL_Rect dialogRect): dialogRect_(dialogRect) 
{
	readFromFile(file);
	characterPortraitSprite = new GameObject(TextureManager::get(spriteText), Vector2D<int>(dialogRect_.x + 200, dialogRect_.y + 345), Vector2D<int>(dialogRect_.w*150, dialogRect_.h*150));

	SDL_Color textColor;
	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;
	textColor.a = 1;

	characterNameSprite = new Text(game->getRenderer(), textFont, Vector2D<int>(dialogRect_.x + 600, dialogRect_.y + 400), textColor, characterName);
	dialogTextSprite = new Text(game->getRenderer(), textFont, Vector2D<int>(dialogRect_.x + 375, dialogRect_.y + 480), textColor, dialogText);
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

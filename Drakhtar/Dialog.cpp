#include "Dialog.h"



Dialog::Dialog(string charName, string diagText)
{
	characterName = charName;
	dialogText = diagText;
}


Dialog::~Dialog()
{
	delete dialogBlockSprite;
	dialogBlockSprite = nullptr;
	delete characterPortraitSprite;
	characterPortraitSprite = nullptr;
	delete characterNameSprite;
	characterNameSprite = nullptr;
	delete dialogTextSprite;
	dialogTextSprite = nullptr;
}

void Dialog::render() const
{
	dialogBlockSprite->render();
	characterPortraitSprite->render();
	characterNameSprite->render();
	dialogTextSprite->render();
}

void Dialog::readFromFile()
{
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Dialog.h"

Dialog::Dialog(Game *game, ifstream &file, Font *textFont, SDL_Rect dialogRect) : dialogRect_(dialogRect)
{
    readFromFile(file);
    characterPortraitSprite = new GameObject(TextureManager::get(spriteText),
                                             Vector2D<int>(dialogRect_.x + dialogRect_.w/8 , dialogRect_.y - dialogRect_.h/3 ),
                                             Vector2D<int>(dialogRect_.h/1.5 , dialogRect_.h/1.5 ));

    SDL_Color textColor;
    textColor.r = 0;
    textColor.g = 0;
    textColor.b = 0;
    textColor.a = 1;

    characterNameSprite = new Text(game->getRenderer(),
                                   textFont,
                                   Vector2D<int>(dialogRect_.x + dialogRect_.w/1.13, dialogRect_.y - dialogRect_.h /10),
                                   textColor,
                                   characterName);
    dialogTextSprite = new Text(game->getRenderer(),
                                textFont,
                                Vector2D<int>(dialogRect_.x + dialogRect_.w / 2.1, dialogRect_.y + dialogRect_.h/2 ),
                                textColor,
                                dialogText);
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

void Dialog::readFromFile(ifstream &file)
{
    file >> characterName;
    file >> spriteText;

    string text;       // full dialog text
    string word = "";  // word added to text each iteration
    while (word != ".")
    {
        file >> word;
        if (word != ".")
            text += word + " ";
    }
    dialogText = text;
}

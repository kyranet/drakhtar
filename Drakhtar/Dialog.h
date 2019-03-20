// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

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
    string spriteText;
    string dialogText;

    GameObject *characterPortraitSprite = nullptr;
    Text *characterNameSprite = nullptr;
    Text *dialogTextSprite = nullptr;

    SDL_Rect dialogRect_;
 public:
    Dialog(Game* game, ifstream& file, Font* textfont, SDL_Rect dialogRect, int lineJumpLimit);
    ~Dialog();
    virtual void render() const;
    void readFromFile(ifstream& file);
};

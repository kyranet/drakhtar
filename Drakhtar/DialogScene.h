// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Dialog.h"
#include "Font.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "checkML.h"

class Game;
class Dialog;

class DialogScene : public GameObject
{
 private:
    GameObject *dialogBlockSprite = nullptr;
    GameObject *characterBlockSprite = nullptr;
    int dialogChainSize = 0;
    vector<Dialog *> dialogChain;
    int currentDialogIndex = 0;
    Font *textFont = nullptr;
    bool destroyedDialog = false;

 public:
    DialogScene(Game *game, string filename, string fontfile);
    ~DialogScene();
    virtual void render() const;
    virtual void handleEvents(SDL_Event event);
    void readFromFile(Game *game, string filename, Font *textFont);
    void nextDialog();
    void endOfDialog();

    GameObject *getBlockSprite() const { return dialogBlockSprite; }
    bool isEndOfDialog() { return destroyedDialog; }
};

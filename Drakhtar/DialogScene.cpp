// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "DialogScene.h"

// Default position and size(adjust it to move DialogScene)
DialogScene::DialogScene(Game *game, string filename, string fontfile) : GameObject(nullptr,
                                                                                    Vector2D<int>(0, 0),
                                                                                    Vector2D<int>(1, 1))
{

	dialogBlockSprite = new GameObject(TextureManager::get("UI-dialogueBackground"),
		Vector2D<int>(getRect().x + WIN_WIDTH / 2, WIN_HEIGHT - getRect().h * WIN_HEIGHT / 6),
		Vector2D<int>(getRect().w * WIN_WIDTH / 1.4, getRect().h * WIN_HEIGHT / 5));

    characterBlockSprite = new GameObject(TextureManager::get("UI-dialogueBackground"),
                                          Vector2D<int>(dialogBlockSprite->getRect().x + dialogBlockSprite->getRect().w - WIN_WIDTH/12, dialogBlockSprite->getRect().y - WIN_HEIGHT/70 ),
                                          Vector2D<int>(getRect().w * WIN_WIDTH/8, getRect().h * WIN_HEIGHT/20));
    textFont = new Font("../fonts/" + fontfile + ".ttf", 12, dialogBlockSprite->getRect().x + 400);
    readFromFile(game, "../dialog/" + filename + ".txt", +textFont);
}

DialogScene::~DialogScene()
{
    for (auto dialog : dialogChain)
        delete dialog;
    delete dialogBlockSprite;
    dialogBlockSprite = nullptr;
    delete characterBlockSprite;
    characterBlockSprite = nullptr;
    delete textFont;
    textFont = nullptr;
}

void DialogScene::render() const
{
    characterBlockSprite->render();
    dialogBlockSprite->render();
    dialogChain[currentDialogIndex]->render();
}

void DialogScene::handleEvents(SDL_Event event) {}

void DialogScene::readFromFile(Game *game, string filename, Font *textFont)
{
    ifstream file;
    file.open(filename);
    /*if (!file.is_open()) throw "No se encuentra el fichero";
    else
    {*/
    file >> dialogChainSize;
    dialogChain.resize(dialogChainSize);

    for (int i = 0; i < dialogChainSize; i++)
    {
        dialogChain[i] = new Dialog(game, file, textFont, dialogBlockSprite->getRect());
    }

    //}
    file.close();
}

void DialogScene::nextDialog()
{
    if (currentDialogIndex < dialogChainSize - 1)
        currentDialogIndex++;
    else
        endOfDialog();
}

void DialogScene::endOfDialog()
{
    destroy();
    destroyedDialog = true;
}

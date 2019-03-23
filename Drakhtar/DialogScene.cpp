// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "DialogScene.h"
#include "Constants.h"
#include "DrakhtarError.h"
#include "FontManager.h"
#include "TextureManager.h"

// default position and size(adjust it to move DialogScene)
DialogScene::DialogScene(Scene *scene, string filename, string fontfile)
    : GameObject(scene, nullptr, Vector2D<int>(0, 0), Vector2D<int>(1, 1)) {
  dialogBlockSprite =
      new GameObject(scene_, TextureManager::get("UI-dialogueBackground"),
                     Vector2D<int>(getRect().x + WIN_WIDTH - 400,
                                   getRect().y + WIN_HEIGHT - 100),
                     Vector2D<int>(getRect().w * 600, getRect().h * 160));
  characterBlockSprite =
      new GameObject(scene_, TextureManager::get("UI-dialogueBackground"),
                     Vector2D<int>(getRect().x + WIN_WIDTH - 197,
                                   getRect().y + WIN_HEIGHT - 190),
                     Vector2D<int>(getRect().w * 120, getRect().h * 32));
  lineJumpLimit_ = dialogBlockSprite->getRect().x + 400;
  textFont = FontManager::get(fontfile);
  readFromFile("../dialog/" + filename + ".txt", textFont);
}

DialogScene::~DialogScene() {
  for (auto dialog : dialogChain) delete dialog;
  delete dialogBlockSprite;
  dialogBlockSprite = nullptr;
  delete characterBlockSprite;
  characterBlockSprite = nullptr;
  textFont = nullptr;
}

void DialogScene::render() const {
  characterBlockSprite->render();
  dialogBlockSprite->render();
  if (currentDialogIndex < dialogChain.size())
    dialogChain[currentDialogIndex]->render();
}

void DialogScene::handleEvents(SDL_Event event) {}

void DialogScene::readFromFile(string filename, Font *textFont) {
  ifstream file;
  file.open(filename);

  if (!file.is_open()) throw new DrakhtarError("Could not find file");

  file >> dialogChainSize;
  dialogChain.resize(dialogChainSize);

  for (int i = 0; i < dialogChainSize; i++) {
    dialogChain[i] =
        new Dialog(scene_, file, textFont, getRect(), lineJumpLimit_);
  }

  file.close();
}

void DialogScene::nextDialog() {
  if (currentDialogIndex < dialogChainSize - 1)
    currentDialogIndex++;
  else
    endOfDialog();
}

void DialogScene::endOfDialog() {
  destroy();
  destroyedDialog = true;
}

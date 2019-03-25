// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "DialogScene.h"
#include "../Errors/DrakhtarError.h"
#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Structures/Font.h"
#include "../Utils/Constants.h"
#include "Dialog.h"

// default position and size(adjust it to move DialogScene)
DialogScene::DialogScene(Scene *scene, string filename, string fontFile)
    : GameObject(scene, nullptr, Vector2D<int>(0, 0), Vector2D<int>(1, 1)) {
  auto area = getRect();
  auto nameBackground = new GameObject(
      scene_, TextureManager::get("UI-dialogueBackground"),
      Vector2D<int>(area.x + WIN_WIDTH - 197, area.y + WIN_HEIGHT - 190),
      Vector2D<int>(area.w * 120, area.h * 32));
  auto dialogueBackground = new GameObject(
      scene_, TextureManager::get("UI-dialogueBackground"),
      Vector2D<int>(area.x + WIN_WIDTH - 400, area.y + WIN_HEIGHT - 100),
      Vector2D<int>(area.w * 600, area.h * 160));

  addChild(nameBackground);
  addChild(dialogueBackground);

  dialogueBackground->addEventListener(
      new DialogSceneOnClick(dialogueBackground));

  lineJumpLimit_ = dialogueBackground->getRect().x + 400;
  readFromFile("../dialog/" + filename + ".txt", FontManager::get(fontFile));
}

DialogScene::~DialogScene() {
  for (auto dialog : dialogues) delete dialog;
}

void DialogScene::render() const {
  GameObject::render();
  dialogues[dialogueIndex]->render();
}

void DialogScene::next() {
  if (dialogueIndex < dialogues.size() - 1)
    dialogueIndex++;
  else
    destroy();
}

void DialogScene::readFromFile(string filename, Font *textFont) {
  ifstream file;
  file.open(filename);

  if (!file.is_open()) throw new DrakhtarError("Could not find file");

  size_t lines, i;
  file >> lines;
  dialogues.resize(lines);
  for (size_t i = 0; i < lines && !file.eof(); i++) {
    dialogues[i] =
        new Dialog(scene_, file, textFont, getRect(), lineJumpLimit_);
  }

  file.close();
}

void DialogSceneOnClick::onClickStop(SDL_Point point) {
  static_cast<DialogScene *>(getGameObject()->getParent())->next();
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "DialogScene.h"
#include "../Errors/DrakhtarError.h"
#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Structures/Font.h"
#include "../Utils/Constants.h"
#include "Dialog.h"

// default position and size(adjust it to move DialogScene)
DialogScene::DialogScene(Scene* scene, const std::string& filename,
                         const std::string& fontFile)
    : GameObject(scene, nullptr, Vector2D<int>(0, 0), Vector2D<int>(1, 1)) {
  const auto area = getRect();
  auto dialogueBackground = new GameObject(
      scene_, TextureManager::get("UI-dialogueBackground"),
      Vector2D<int>(area.x + WIN_WIDTH / 2,
                    WIN_HEIGHT - area.h * WIN_HEIGHT / 6),
      Vector2D<int>(area.w * WIN_WIDTH / 1.4, area.h * WIN_HEIGHT / 5));
  const auto nameBackground = new GameObject(
      scene_, TextureManager::get("UI-dialogueBackground"),
      Vector2D<int>(dialogueBackground->getRect().x +
                        dialogueBackground->getRect().w - WIN_WIDTH / 12,
                    dialogueBackground->getRect().y - WIN_WIDTH / 70),
      Vector2D<int>(area.w * WIN_WIDTH / 8, area.h * WIN_HEIGHT / 20));

  addChild(nameBackground);
  addChild(dialogueBackground);

  dialogueBackground->addEventListener(
      new DialogSceneOnClick(dialogueBackground));

  lineJumpLimit_ = dialogueBackground->getRect().x + WIN_WIDTH / 2;
  readFromFile("../dialog/" + filename + ".txt", FontManager::get(fontFile),
               dialogueBackground->getRect());
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

void DialogScene::readFromFile(const std::string& filename, Font* textFont,
                               SDL_Rect rect) {
  std::ifstream file;
  file.open(filename);

  if (!file.is_open()) throw new DrakhtarError("Could not find file");

  size_t lines, i;
  file >> lines;
  dialogues.resize(lines);
  for (size_t i = 0; i < lines && !file.eof(); i++) {
    dialogues[i] = new Dialog(scene_, file, textFont, rect, lineJumpLimit_);
  }

  file.close();
}

void DialogSceneOnClick::onClickStop(SDL_Point point) {
  static_cast<DialogScene*>(getGameObject()->getParent())->next();  // NOLINT
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "DialogScene.h"

#include <fstream>
#include <iostream>

#include "Dialog.h"
#include "Errors/DrakhtarError.h"
#include "EventListeners/DialogSceneOnClick.h"
#include "GameObjects/Button.h"
#include "Managers/FontManager.h"
#include "Managers/GameManager.h"
#include "Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/RecruitScene.h"
#include "Scenes/Scene.h"
#include "Scenes/TransitionScene.h"
#include "Structures/Font.h"
#include "Structures/Game.h"
#include "Utils/Constants.h"

// default position and size(adjust it to move DialogScene)
DialogScene::DialogScene(Scene* scene, const std::string& filename,
                         const std::string& fontFile)
    : Sequence(scene, nullptr, Vector2D<int>(0, 0), Vector2D<int>(1, 1)) {
  const auto area = GameObject::getRect();
  auto dialogueBackground =
      new GameObject(scene_, TextureManager::get("UI-dialogueBackground"),
                     Vector2D<int>(area.x + WIN_WIDTH / 2,
                                   WIN_HEIGHT - area.h * WIN_HEIGHT / 6),
                     Vector2D<int>(static_cast<int>(area.w * WIN_WIDTH / 1.4),
                                   area.h * WIN_HEIGHT / 4));
  const auto nameBackground = new GameObject(
      scene_, TextureManager::get("UI-dialogueBackground"),
      Vector2D<int>(dialogueBackground->getRect().x +
                        dialogueBackground->getRect().w - WIN_WIDTH / 12,
                    dialogueBackground->getRect().y - WIN_WIDTH / 70),
      Vector2D<int>(area.w * WIN_WIDTH / 8, area.h * WIN_HEIGHT / 20));
  const auto arrow = new Button(
      scene_, TextureManager::get("UI-dialogueArrow"),
      Vector2D<int>(
          dialogueBackground->getRect().x + dialogueBackground->getRect().w / 2,
          dialogueBackground->getRect().y + 140),
      Vector2D<int>(area.w * WIN_WIDTH / 8, area.h * WIN_HEIGHT / 10), {}, " ",
      "ButtonFont");
  arrow->setTransparent(true);
  const auto skipButton = new Button(
      scene_, TextureManager::get("Button-Skip"),
      Vector2D<int>(static_cast<int>(dialogueBackground->getRect().x +
                                     dialogueBackground->getRect().w / 1.05),
                    dialogueBackground->getRect().y + 140),
      Vector2D<int>(area.w * WIN_WIDTH / 30, area.h * WIN_HEIGHT / 24),
      [this]() { skip(); }, " ", "ButtonFont");

  addChild(nameBackground);
  addChild(dialogueBackground);
  addChild(arrow);
  addChild(skipButton);

  dialogueBackground->addEventListener(
      new DialogSceneOnClick(dialogueBackground));

  lineJumpLimit_ = dialogueBackground->getRect().x + WIN_WIDTH / 2;
  readFromFile("../dialog/" + filename + ".txt", FontManager::get(fontFile),
               dialogueBackground->getRect());
}

DialogScene::~DialogScene() {
  for (auto dialog : dialogues_) delete dialog;
}

void DialogScene::render() const {
  GameObject::render();
  dialogues_[dialogueIndex_]->render();
}

void DialogScene::next() {
  if (dialogueIndex_ < dialogues_.size() - 1) {
    ++dialogueIndex_;
  } else {
    destroy();
    skip();
  }
}

void DialogScene::skip() {
  destroy();
  if (Game::getSceneMachine()->getCurrentScene()->getTransition()) {
    int scene = reinterpret_cast<TransitionScene*>(getScene())->getBattleInd();

    if (scene < 3) {
      Game::getSceneMachine()->changeScene(new GameScene(scene));
    } else {
      GameManager::getInstance()->reset();
      Game::getSceneMachine()->changeScene(new MenuScene());
    }
  }
}

void DialogScene::readFromFile(const std::string& filename, Font* textFont,
                               const SDL_Rect rect) {
  std::ifstream file;
  file.open(filename);

  if (!file.is_open()) throw DrakhtarError("Could not find file");

  size_t lines;
  file >> lines;
  dialogues_.resize(lines);
  for (size_t i = 0; i < lines && !file.eof(); i++) {
    dialogues_[i] = new Dialog(scene_, file, textFont, rect, lineJumpLimit_);
  }

  file.close();
}

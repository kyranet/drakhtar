// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TutorialSequence.h"

#include "Errors/DrakhtarError.h"
#include "EventListeners/TutorialSceneOnClick.h"
#include "GameObjects/Button.h"
#include "Managers/FontManager.h"
#include "Managers/TextureManager.h"
#include "Scenes/Scene.h"
#include "Structures/Font.h"
#include "Structures/Game.h"
#include "TutorialBox.h"
#include "Utils/Constants.h"

TutorialSequence::TutorialSequence(Scene* scene, const std::string& filename,
                                   const std::string& fontFile)
    : Sequence(scene, nullptr, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
               Vector2D<int>(1, 1)) {
  const auto tutorialArea_ = getRect();

  auto dialogueBackground = new GameObject(
      scene_, TextureManager::get("UI-tutorialBackground"),
      Vector2D<int>(tutorialArea_.x, tutorialArea_.y - WIN_HEIGHT / 10),
      Vector2D<int>(tutorialArea_.w * WIN_WIDTH / 2,
                    tutorialArea_.h * WIN_HEIGHT / 1.5));

  const auto nextButton = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(tutorialArea_.x - WIN_WIDTH / 10,
                    tutorialArea_.y + WIN_HEIGHT / 10),
      Vector2D<int>(WIN_WIDTH / 13, WIN_HEIGHT / 19), [this]() { next(); },
      "Next", "ButtonFont");
  nextButton->setTransparent(false);

  const auto closeButton = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(tutorialArea_.x + WIN_WIDTH / 10,
                    tutorialArea_.y + WIN_HEIGHT / 10),
      Vector2D<int>(WIN_WIDTH / 13, WIN_HEIGHT / 19), [this]() { skip(); },
      "Close", "ButtonFont");
  closeButton->setTransparent(false);

  addChild(dialogueBackground);
  addChild(closeButton);
  addChild(nextButton);

  readFromFile("../tutorials/" + filename + ".txt", FontManager::get(fontFile),
               tutorialArea_, dialogueBackground->getRect());

  dialogueBackground->addEventListener(
      new TutorialSceneOnClick(dialogueBackground));
}

TutorialSequence::~TutorialSequence() {
  while (!tutorials_.empty()) {
    delete tutorials_.front();
    tutorials_.pop();
  }
}

void TutorialSequence::readFromFile(const std::string& filename, Font* textFont,
                                    SDL_Rect tutorialArea,
                                    SDL_Rect dialogueBackground) {
  std::ifstream file;
  file.open(filename);
  if (!file.is_open()) throw DrakhtarError("Could not find file");

  size_t lines;
  file >> lines;

  for (size_t i = 0; i < lines && !file.eof(); i++) {
    tutorials_.push(new TutorialBox(scene_, file, textFont, tutorialArea,
                                    dialogueBackground));
  }

  file.close();

  if (tutorials_.empty()) destroy();
}

void TutorialSequence::next() {
  delete tutorials_.front();
  tutorials_.pop();

  if (tutorials_.empty()) skip();
}

void TutorialSequence::skip() { destroy(); }

void TutorialSequence::render() const {
  if (!tutorials_.empty()) {
    GameObject::render();
    tutorials_.front()->render();
  }
}

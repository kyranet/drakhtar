// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "CreditsScene.h"

#include "../Errors/DrakhtarError.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/GameObject.h"
#include "../Managers/FontManager.h"
#include "../Managers/SDLAudioManager.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/Scene.h"
#include "../Structures/Game.h"
#include "../Utils/Constants.h"

CreditsScene::CreditsScene() {}

CreditsScene::~CreditsScene() = default;

void CreditsScene::preload() {
  file_.open("../levels/credits.txt");
  if (!file_.is_open()) throw DrakhtarError("Could not find file");

  file_ >> creditsLength_;

  const SDL_Color textColor = {255, 255, 255, 0};

  const auto menuButton_ = new Button(
      this, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(WIN_WIDTH - 100, WIN_HEIGHT - 50),
      Vector2D<int>(WIN_WIDTH / 8, WIN_HEIGHT / 8),
      [this]() { Game::getSceneMachine()->changeScene(new MenuScene()); },
      "Menu", "ButtonFont");
  addGameObject(menuButton_);

  creditText1_ =
      new CreditText(this, FontManager::get("TutorialFont"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT), textColor,
                     getNextLine(), 1000, 2, creditsLength_);
  readCredits_++;
  addGameObject(creditText1_);

  creditText2_ =
      new CreditText(this, FontManager::get("TutorialFont"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT + WIN_HEIGHT / 2),
                     textColor, getNextLine(), 1000, 2, creditsLength_);
  readCredits_++;
  addGameObject(creditText2_);

  auto audio = SDLAudioManager::getInstance();
  audio->playMusic(6, -1);
}

std::string CreditsScene::getNextLine() {
  std::string text;  // full dialog text
  std::string word;  // word added to text each iteration
  while (word != ".") {
    file_ >> word;
    if (word != ".") text += word + " ";
  }
  return text;
}

int CreditsScene::getReadCredits() { return readCredits_; }

void CreditsScene::setReadCredits(int readCredits) {
  readCredits_ = readCredits;
}

bool CreditsScene::getLastCredit() { return lastCredit_; }

void CreditsScene::setLastCredit(bool lastCredit) { lastCredit_ = lastCredit; }

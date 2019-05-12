#include "CreditsScene.h"

#include "../Errors/DrakhtarError.h"
#include "../GameObjects/Button.h"
#include "../Managers/FontManager.h"
#include "../Managers/SDLAudioManager.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/Scene.h"
#include "../Structures/Game.h"
#include "../Utils/Constants.h"

auto audio = SDLAudioManager::getInstance();

CreditsScene::CreditsScene() {}

CreditsScene::~CreditsScene() { delete creditText_; }

void CreditsScene::preload() {
  std::ifstream file;
  file.open("../levels/credits.txt");
  if (!file.is_open()) throw DrakhtarError("Could not find file");

  file >> creditsLength_;

  const SDL_Color textColor = {0, 0, 0, 255};

  std::string firstCredit = getNextLine(file);
  readCredits_++;

  creditText_ = new CreditText(this, FontManager::get("TutorialFont"),
                               Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT),
                               textColor, firstCredit, 500, 0.1);

  const auto menuButton_ = new Button(
      this, TextureManager::get("Vanilla-Button"), Vector2D<int>(80, 80),
      Vector2D<int>(80, 80),
      [this]() { Game::getSceneMachine()->changeScene(new MenuScene()); },
      "Menu", "ButtonFont");

  addGameObject(creditText_);
  addGameObject(menuButton_);
}

void CreditsScene::readNextLine() {}

std::string CreditsScene::getNextLine(std::ifstream file) {
  std::string text;  // full dialog text
  std::string word;  // word added to text each iteration
  while (word != ".") {
    file >> word;
    if (word != ".") text += word + " ";
  }
  return text;
}

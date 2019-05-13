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

  std::string firstCredit = getNextLine();
  readCredits_++;

  const auto menuButton_ = new Button(
      this, TextureManager::get("Vanilla-Button"), Vector2D<int>(80, 80),
      Vector2D<int>(80, 80),
      [this]() { Game::getSceneMachine()->changeScene(new MenuScene()); },
      "Menu", "ButtonFont");
  addGameObject(menuButton_);

  creditText_ = new CreditText(this, FontManager::get("TutorialFont"),
                               Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT),
                               textColor, firstCredit, 1000, 2, creditsLength_);
  addGameObject(creditText_);

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

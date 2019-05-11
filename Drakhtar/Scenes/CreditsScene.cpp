#include "CreditsScene.h"


#include "../Errors/DrakhtarError.h"
#include "../Managers/FontManager.h"
#include "../Managers/SDLAudioManager.h"
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

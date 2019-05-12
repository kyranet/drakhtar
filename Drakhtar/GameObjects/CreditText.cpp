#include "CreditText.h"

#include "../Scenes/CreditsScene.h"
#include "../Scenes/MenuScene.h"
#include "../Structures/Game.h"
#include "../Utils/Constants.h"

CreditText::CreditText(Scene* scene, Font* font, Vector2D<int> position,
                       SDL_Color color, const std::string& text,
                       int lineJumpLimit, double speed, int creditsLength)
    : Text(scene, font, position, color, text, lineJumpLimit),
      speed_(speed),
      creditsLength_(creditsLength) {}

CreditText::~CreditText() = default;

void CreditText::update() {
  if (getPosition().getY() > 0)
    move();
  else
    nextLine();
}

void CreditText::move() {
  this->setPosition(
      Vector2D<int>(getPosition().getX(), getPosition().getY() - speed_));
}

void CreditText::nextLine() {
  if (readCredits_ < creditsLength_) {
    std::string line = reinterpret_cast<CreditsScene*>(scene_)->getNextLine();
    this->setText(line);
    this->setPosition(Vector2D<int>(getPosition().getX(), WIN_HEIGHT));
  }
  else
  {
    Game::getSceneMachine()->changeScene(new MenuScene());
  }
}

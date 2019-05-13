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
      creditsLength_(creditsLength) {
  setColor(color);
}

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
    setText(line);
    const SDL_Color textColor = {255, 255, 255, 0};
    setColor(textColor);
    setPosition(Vector2D<int>(getPosition().getX(), WIN_HEIGHT));
    readCredits_++;
  } else {
    Game::getSceneMachine()->changeScene(new MenuScene());
  }
}

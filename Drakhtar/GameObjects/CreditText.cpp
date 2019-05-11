#include "CreditText.h"

#include "../Utils/Constants.h"

CreditText::CreditText(Scene* scene, Font* font, Vector2D<int> position,
                       SDL_Color color, const std::string& text,
                       int lineJumpLimit, double speed)
    : Text(scene, font, position, color, text, lineJumpLimit), speed_(speed) {}

CreditText::~CreditText() = default;

void CreditText::update() {
  if (getPosition().getY() > 0)
    move();
  else
    nextLine();
}

void CreditText::move() {
  Vector2D<int>(getPosition().getX(), getPosition().getY() - speed_);
}

void CreditText::nextLine() {
  up_ = true;
  setPosition(Vector2D<int>(getPosition().getX(), WIN_HEIGHT));
}

bool CreditText::getUp() { return up_; }

void CreditText::setUp(bool up) { up_ = up; }

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

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
  if (getPosition().getY() > -20) {
    move();
  } else if (!lastCredit_) {
    nextLine();
  }
}

void CreditText::move() {
  this->setPosition(
      Vector2D<int>(static_cast<int>(getPosition().getX()),
                    static_cast<int>(getPosition().getY() - speed_)));
}

void CreditText::nextLine() {
  CreditsScene* scene = reinterpret_cast<CreditsScene*>(scene_);
  if (scene->getReadCredits() < creditsLength_) {
    std::string line = scene->getNextLine();
    setText(line);
    const SDL_Color textColor = {255, 255, 255, 0};
    setColor(textColor);
    setPosition(Vector2D<int>(getPosition().getX(), WIN_HEIGHT));
    scene->setReadCredits(scene->getReadCredits() + 1);
  } else {
    if (scene->getLastCredit()) {
      Game::getSceneMachine()->changeScene(new MenuScene());
    } else {
      scene->setLastCredit(true);
      lastCredit_ = true;
    }
  }
}

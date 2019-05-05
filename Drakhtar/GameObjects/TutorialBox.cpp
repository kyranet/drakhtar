// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TutorialBox.h"
#include "EventListeners/TutorialSceneOnClick.h"
#include "../GameObjects/Button.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Structures/Font.h"
#include "../Utils/Constants.h"
#include "GameObject.h"
#include "Text.h"

TutorialBox::TutorialBox(Scene *scene, std::ifstream &file, Font *textFont)
    : GameObject(scene, nullptr, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                 Vector2D<int>(1, 1)) {
  readFromFile(file);

  const auto lineJumpLimit = static_cast<int>(480 * 0.75);

  const auto tutorialImage =
      new GameObject(scene, TextureManager::get(imageText_),
                     Vector2D<int>(posX, posY - WIN_HEIGHT / 7),
                     Vector2D<int>(640 - WIN_WIDTH / 5, 640 - WIN_HEIGHT / 1.65));

  const SDL_Color textColor = {255, 255, 255, 255};

  const auto tutorialTextSprite = new Text(
      scene_, textFont, Vector2D<int>(posX, posY - WIN_HEIGHT / 10),
      textColor, dialogText_, lineJumpLimit);

  const auto dialogueBackgroundBox = new GameObject(
      scene_, TextureManager::get("UI-tutorialBackground"),
      Vector2D<int>(posX, posY),
      Vector2D<int>(640, 480));
  
  tutorialTextSprite->setColor(textColor);
  tutorialTextSprite->setText(dialogText_, textColor, lineJumpLimit);
  tutorialTextSprite->setPosition({posX, posY + 50});

  addChild(dialogueBackgroundBox);
  addChild(tutorialImage);
  addChild(tutorialTextSprite);
  dialogueBackgroundBox->addEventListener(
    new TutorialSceneOnClick(dialogueBackgroundBox));
}

void TutorialBox::readFromFile(std::ifstream &file) {
  file >> posX;
  file >> posY;
  file >> renderizable;
  file >> imageText_;

  std::string text;  // full dialog text
  std::string word;  // word added to text each iteration
  while (word != ".") {
    file >> word;
    if (word != ".")
      text += word + " ";
  }
  dialogText_ = text;
}

bool TutorialBox::getVisible() {
  if (renderizable == "renderizable") return true;
  else return false;
}


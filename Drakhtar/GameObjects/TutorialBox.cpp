// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TutorialBox.h"
#include "../GameObjects/Button.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Structures/Font.h"
#include "../Utils/Constants.h"
#include "GameObject.h"
#include "Text.h"

TutorialBox::TutorialBox(Scene *scene, std::ifstream &file, Font *textFont,
                         const SDL_Rect tutorialArea,
                         const SDL_Rect dialogueBackground)
    : GameObject(scene, nullptr, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                 Vector2D<int>(1, 1)) {
  readFromFile(file);

  const auto lineJumpLimit = static_cast<int>(dialogueBackground.w * 0.75);

  const auto tutorialImage = new GameObject(
      scene, TextureManager::get(imageText_),
      Vector2D<int>(tutorialArea.x,
                    dialogueBackground.y + dialogueBackground.h / 3.25),
      Vector2D<int>(tutorialArea.h * WIN_WIDTH / 3,
                    tutorialArea.h * WIN_HEIGHT / 3));

  const SDL_Color textColor = {255, 255, 255, 255};

  const auto tutorialTextSprite =
      new Text(scene_, textFont,
               Vector2D<int>(tutorialArea.x + dialogueBackground.w / 80,
                             tutorialArea.y - dialogueBackground.h / 80),
               textColor, dialogText_, lineJumpLimit);

  tutorialTextSprite->setColor(textColor);
  tutorialTextSprite->setText(dialogText_, textColor, lineJumpLimit);

  addChild(tutorialImage);
  addChild(tutorialTextSprite);
}

void TutorialBox::readFromFile(std::ifstream &file) {
  file >> imageText_;

  std::string text; // full dialog text
  std::string word; // word added to text each iteration
  while (word != ".") {
    file >> word;
    if (word != ".")
      text += word + " ";
  }
  dialogText_ = text;
}

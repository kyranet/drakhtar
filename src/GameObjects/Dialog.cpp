// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Dialog.h"

#include <fstream>
#include <iostream>

#include "../Managers/TextureManager.h"
#include "../Structures/Font.h"
#include "GameObject.h"
#include "Structures/Game.h"
#include "Text.h"

Dialog::Dialog(Scene* scene, std::ifstream& file, Font* textFont,
               const SDL_Rect dialogRect, const int lineJumpLimit)
    : GameObject(scene, nullptr), dialogueArea_(dialogRect) {
  readFromFile(file);

  const auto characterPortraitSprite =
      new GameObject(scene, TextureManager::get(spriteText_),
                     Vector2D<int>(dialogueArea_.x + dialogueArea_.w / 8,
                                   dialogueArea_.y - dialogueArea_.h / 2),
                     Vector2D<int>(dialogueArea_.h / 1, dialogueArea_.h / 1));

  const SDL_Color textColor = {0, 0, 0, 255};

  const auto characterNameSprite = new Text(
      scene_, textFont,
      Vector2D<int>(static_cast<int>(dialogueArea_.x + dialogueArea_.w / 1.13),
                    dialogueArea_.y - dialogueArea_.h / 9),
      textColor, characterName_, lineJumpLimit);

  const auto dialogTextSprite =
      new Text(scene_, textFont,
               Vector2D<int>(dialogueArea_.x + dialogueArea_.w / 2,
                             dialogueArea_.y + dialogueArea_.h / 2),
               textColor, dialogText_, lineJumpLimit);

  addChild(characterPortraitSprite);
  addChild(characterNameSprite);
  addChild(dialogTextSprite);
}

void Dialog::readFromFile(std::ifstream& file) {
  file >> characterName_;
  file >> spriteText_;

  std::string text;  // full dialog text
  std::string word;  // word added to text each iteration
  while (word != ".") {
    file >> word;
    if (word != ".") text += word;
  }
  dialogText_ = Game::getInstance()->getLocale()->format(text);
}

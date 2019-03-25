// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Dialog.h"
#include "../Managers/TextureManager.h"
#include "../Structures/Font.h"
#include "GameObject.h"
#include "Text.h"

Dialog::Dialog(Scene* scene, std::ifstream& file, Font* textfont,
               SDL_Rect dialogRect, int lineJumpLimit)
    : GameObject(scene, nullptr), dialogueArea_(dialogRect) {
  readFromFile(file);

  auto characterPortraitSprite = new GameObject(
      scene, TextureManager::get(spriteText_),
      Vector2D<int>(dialogueArea_.x + 200, dialogueArea_.y + 345),
      Vector2D<int>(dialogueArea_.w * 150, dialogueArea_.h * 150));

  SDL_Color textColor = {0, 0, 0, 1};

  auto characterNameSprite =
      new Text(scene_, textfont,
               Vector2D<int>(dialogueArea_.x + 600, dialogueArea_.y + 405),
               textColor, characterName_, lineJumpLimit);

  auto dialogTextSprite =
      new Text(scene_, textfont,
               Vector2D<int>(dialogueArea_.x + 375, dialogueArea_.y + 480),
               textColor, dialogText_, lineJumpLimit);

  addChild(characterPortraitSprite);
  addChild(characterNameSprite);
  addChild(dialogTextSprite);
}

void Dialog::readFromFile(std::ifstream& file) {
  file >> characterName_;
  file >> spriteText_;

  std::string text;       // full dialog text
  std::string word = "";  // word added to text each iteration
  while (word != ".") {
    file >> word;
    if (word != ".") text += word + " ";
  }
  dialogText_ = text;
}

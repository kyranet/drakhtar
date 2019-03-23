// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Dialog.h"
#include "Font.h"
#include "GameObject.h"
#include "Text.h"
#include "TextureManager.h"

// TODO(Antonio Román): Add GameObject::children

Dialog::Dialog(Scene* scene, std::ifstream& file, Font *textfont,
               SDL_Rect dialogRect, int lineJumpLimit)
    : GameObject(scene, nullptr), dialogRect_(dialogRect) {
  readFromFile(file);
  characterPortraitSprite =
      new GameObject(scene, TextureManager::get(spriteText),
                     Vector2D<int>(dialogRect_.x + 200, dialogRect_.y + 345),
                     Vector2D<int>(dialogRect_.w * 150, dialogRect_.h * 150));

  SDL_Color textColor = {0, 0, 0, 1};

  characterNameSprite =
      new Text(scene_, textfont,
               Vector2D<int>(dialogRect_.x + 600, dialogRect_.y + 405),
               textColor, characterName, lineJumpLimit);

  dialogTextSprite =
      new Text(scene_, textfont,
               Vector2D<int>(dialogRect_.x + 375, dialogRect_.y + 480),
               textColor, dialogText, lineJumpLimit);
}

Dialog::~Dialog() {
  delete characterPortraitSprite;
  characterPortraitSprite = nullptr;
  delete characterNameSprite;
  characterNameSprite = nullptr;
  delete dialogTextSprite;
  dialogTextSprite = nullptr;
}

void Dialog::render() const {
  characterPortraitSprite->render();
  characterNameSprite->render();
  dialogTextSprite->render();
}

void Dialog::readFromFile(ifstream& file) {
  file >> characterName;
  file >> spriteText;

  string text;       // full dialog text
  string word = "";  // word added to text each iteration
  while (word != ".") {
    file >> word;
    if (word != ".") text += word + " ";
  }
  dialogText = text;
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TutorialText.h"

#include "../Managers/FontManager.h"
#include "../Managers/GameManager.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Structures/Font.h"
#include "../Utils/Vector2D.h"
#include "GameObjects/Button.h"
#include "GameObjects/Unit.h"
#include "Structures/Game.h"
#include "Structures/UnitFactory.h"
#include "Text.h"
#include "TutorialBox.h"

TutorialText::TutorialText(Scene* scene, std::string& file, SDL_Rect rect)
    : GameObject(scene, TextureManager::get("Reward-Panel"),
                 Vector2D<int>(400, 400), Vector2D<int>(1000, 1000)) {
  readFromFile(file);
  text_ = new Text(scene, FontManager::get("Retron2000"),
                   Vector2D<int>(rect.x, static_cast<int>(rect.y * 0.9)),
                   {255, 255, 255, 1}, texts[cont].dialogtexts_, 250);
  text_->setRenderizable(true);
  text_->setTransparent(true);
  text_->setColor({255, 255, 255, 0});
  addChild(text_);
}

TutorialText::~TutorialText() { texts.clear(); }

void TutorialText::render() const { text_->render(); }

void TutorialText::readFromFile(std::string& filename) {
  std::ifstream file;
  file.open(filename);
  std::string text;  // full dialog text
  std::string word;  // word added to text each iteration
  int limit = 0;
  file >> limit;

  bool next = false;
  int finished = false;
  int i = 0;
  while (!finished && i < limit) {
    file >> word;
    if ((word != "¡" && word != ".")) text += word + " ";
    if (word == "¡") next = true;
    if (word == ".") {
      TutorialTexts TutorialFileText;
      text.erase(0, 10);
      TutorialFileText.dialogtexts_ = text;
      TutorialFileText.next_ = next;
      texts.push_back(TutorialFileText);
      text = "";
      next = false;
      i++;
    }
  }

  file.close();
}

bool TutorialText::addCount() {
  if (cont + 1 == texts.size()) {
    return false;
  } else {
    ++cont;
    text_->setText(texts[cont].dialogtexts_);
    text_->setColor({255, 255, 255, 0});
    return true;
  }
}

bool TutorialText::getClosed(int x) { return texts[x].next_; }

int TutorialText::getCont() const { return cont; }

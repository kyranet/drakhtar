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

TutorialText::TutorialText(Scene* scene, TutorialBox* box, std::string& file)
    : GameObject(scene, TextureManager::get("Reward-Panel"),
                 Vector2D<int>(400,400), Vector2D<int>(1000,1000)) {
  readFromFile(file);
  auto text =
      new Text(scene, FontManager::get("SkillButtonFont"),{400,400}, {0, 0, 0, 1},
               returnTutorialText(), WIN_WIDTH * 0.9);
  text->setRenderizable(true);
	box->addChild(text);
}

TutorialText::~TutorialText() { texts.clear(); }

void TutorialText::render() const {}

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

std::string TutorialText::returnTutorialText() {
  return texts[cont].dialogtexts_;
}

void TutorialText::addCount() { cont++; }

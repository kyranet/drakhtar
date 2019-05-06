// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TutorialBox.h"
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

TutorialText::TutorialText(Scene* scene, TutorialBox* box, std::string& file)
    : GameObject(scene, TextureManager::get("Reward-Panel"),Vector2D<int>(1,1),
                 Vector2D<int>(1,1)) 
				 {
  readFromFile(file);
  std::cout << "s";
				 }

void TutorialText::render() const {}

void TutorialText::readFromFile(std::string& filename) {
  std::ifstream file;
  file.open(filename);
  std::string text;  // full dialog text
  std::string word;  // word added to text each iteration
  int limit = 0;  file >> limit;

  for (int i = 0; i < limit; i++)
  {
    while (word != ".") {
      file >> word;
      texts[i].dialogtexts_ += word;
      if (word == "¡") {
        texts[i].next_ = true;
      } else
        texts[i].next_ = false;

    }
  }
  texts[1].next_ = false;
  file.close();
}

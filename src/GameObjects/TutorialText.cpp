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

TutorialText::TutorialText(Scene* scene, SDL_Rect rect)
    : GameObject(scene, TextureManager::get("Reward-Panel"),
                 Vector2D<int>(400, 400), Vector2D<int>(1000, 1000)) {
  readFromLocale();
  text_ = new Text(scene, FontManager::get("Retron2000"),
                   Vector2D<int>(rect.x, static_cast<int>(rect.y * 0.9)),
                   {255, 255, 255, 1}, texts[cont], 250);
  text_->setRenderable(true);
  text_->setTransparent(true);
  text_->setColor({255, 255, 255, 0});
  addChild(text_);
}

TutorialText::~TutorialText() { texts.clear(); }

void TutorialText::render() const { text_->render(); }

void TutorialText::readFromLocale() {
  for (int i = 1; i <= 17; i++) {
    texts.push_back(Game::getInstance()->getLocale()->format(
        "tutorial" + std::to_string(i)));
  }
}

bool TutorialText::addCount() {
  if (cont + 1 == texts.size()) {
    return false;
  } else {
    ++cont;
    text_->setText(texts[cont]);
    text_->setColor({255, 255, 255, 0});
    return true;
  }
}

bool TutorialText::getClosed(int x) { return x != 16; }

int TutorialText::getCont() const { return cont; }

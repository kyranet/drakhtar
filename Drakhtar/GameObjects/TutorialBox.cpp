// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TutorialBox.h"

#include "../GameObjects/Button.h"
#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Structures/Font.h"
#include "../Utils/Constants.h"
#include "EventListeners/TutorialSceneOnClick.h"
#include "GameObject.h"
#include "Text.h"
#include "TutorialText.h"

TutorialBox::TutorialBox(Scene* scene, std::string& filename, Vector2D<int> pos,
                         Vector2D<int> size)
    : GameObject(scene, nullptr, pos, size) {
  SDL_Rect rect = {pos.getX(), pos.getY(), size.getX(), size.getY()};
  auto tutorialText_ = new TutorialText(scene, this, filename, rect);

  const auto tutorialBackground =
      new GameObject(scene, TextureManager::get("UI-tutorialBackground"),
                     Vector2D<int>(rect.x, rect.y * 1.1),
                     Vector2D<int>(rect.w * 1.3, rect.h * 1.3));

  const auto nextButton = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(tutorialBackground->getPosition().getX() -
                        tutorialBackground->getRect().w / 4,
                    tutorialBackground->getPosition().getY() +
                        tutorialBackground->getRect().h / 4),
      Vector2D<int>(WIN_WIDTH / 13, WIN_HEIGHT / 19),
      [tutorialText_, this]() {
        if (!tutorialText_->addCount()) {
          for (auto child : getChildren()) {
            child->setRenderizable(false);
            child->setTransparent(true);
          }
        }
      },
      "Next ", "ButtonFont");
  const auto CloseButton = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(tutorialBackground->getRect().w / 4 +
                        tutorialBackground->getPosition().getX(),
                    tutorialBackground->getPosition().getY() +
                        tutorialBackground->getRect().h / 4),
      Vector2D<int>(WIN_WIDTH / 14, WIN_HEIGHT / 20),
      [tutorialText_, this]() {
        tutorialText_->closeAddCount();
        for (auto child : getChildren()) {
          child->setRenderizable(false);
          child->setTransparent(true);
        }
      },
      "Close ", "ButtonFont");

  addChild(tutorialBackground);
  addChild(tutorialText_);
  addChild(nextButton);
  addChild(CloseButton);
}

void TutorialBox::setBoxPosition(Vector2D<int> pos) {}

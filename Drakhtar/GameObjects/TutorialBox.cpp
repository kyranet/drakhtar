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
#include "Structures/Game.h"
#include "Text.h"
#include "TutorialText.h"
TutorialBox::TutorialBox(Scene* scene, std::string& filename, Vector2D<int> pos,
                         Vector2D<int> size)
    : GameObject(scene, nullptr, pos, size) {
  SDL_Rect rect = {pos.getX(), pos.getY(), size.getX(), size.getY()};
  auto tutorialText_ = new TutorialText(scene, this, filename, rect);

  auto arrow = new GameObject(scene, TextureManager::get("UI-arrowAnim"),
                              Vector2D<int>(400, 400),
                              Vector2D<int>(WIN_WIDTH / 20, WIN_WIDTH / 20));

  arrow->getTexture()->setFlip(SDL_FLIP_HORIZONTAL);

  auto counter = 0;
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
      [tutorialText_, this, counter,scene]() {
        switch (counter) {
          case 1:
              
            break;
          case 2:
            break;
          case 3:
            break;
        }
        if (!tutorialText_->getClosed(tutorialText_->getCont() + 1)) {
          setNextButtonRender(false);
          setCloseButtonRender(true);
        }
        if (!tutorialText_->addCount()) {
          this->setRenderizable(false);
          this->setTransparent(true);
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
      [tutorialText_, this, counter]() mutable {
        if (counter == 0) {
          counter++;
        }
        tutorialText_->closeAddCount();
        this->setRenderizable(false);
        this->setTransparent(true);
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
  setCloseButtonRender(false);
  addChild(arrow);
  setArrowRenderizable(false);
}

void TutorialBox::setNextButtonRender(bool next) {
  getChildren()[2]->setRenderizable(next);
  getChildren()[2]->setTransparent(!next);
}

void TutorialBox::setCloseButtonRender(bool close) {
  getChildren()[3]->setRenderizable(close);
  getChildren()[3]->setTransparent(!close);
}

void TutorialBox::setArrowPos(SDL_RendererFlip flip, Vector2D<int> pos) {
  getChildren()[4]->setPosition(pos);
  getChildren()[4]->getTexture()->setFlip(flip);
}

void TutorialBox::setArrowRenderizable(bool renderizable) {
  getChildren()[4]->setRenderizable(renderizable);
}

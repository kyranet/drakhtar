// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TutorialBox.h"

#include "../GameObjects/Button.h"
#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Structures/Font.h"
#include "../Utils/Constants.h"
#include "Controllers/PlayerController.h"
#include "GameObject.h"
#include "Structures/Game.h"
#include "Text.h"
#include "TutorialText.h"
#include "Unit.h"
TutorialBox::TutorialBox(Scene* scene, std::string& filename, Vector2D<int> pos,
                         Vector2D<int> size, PlayerController* controller,
                         PlayerController* temporalController)
    : GameObject(scene, nullptr, pos, size) {
  SDL_Rect rect = {pos.getX(), pos.getY(), size.getX(), size.getY()};
  auto tutorialText_ = new TutorialText(scene, this, filename, rect);

  auto arrow = new GameObject(scene, TextureManager::get("UI-arrowAnim"),
                              Vector2D<int>(400, 400),
                              Vector2D<int>(WIN_WIDTH / 20, WIN_WIDTH / 20));

  arrow->getTexture()->setFlip(SDL_FLIP_HORIZONTAL);

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
      [tutorialText_, this, tutorialBackground, scene, controller]() {
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
        Vector2D<int> pos = {0, 0};
        int x = tutorialText_->getCont();
        if (x == 9) {
          setArrowRenderizable(true);
          pos = Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 1.8,
                              WIN_HEIGHT - WIN_HEIGHT / 13);
          setArrowPos(SDL_FLIP_NONE, pos);
        }
        if (x == 10) {
          pos = controller->getActiveUnit()->getPosition();
          if (pos.getX() < WIN_WIDTH / 2) {
            pos.setX(pos.getX() - WIN_WIDTH / 15);
            setArrowPos(SDL_FLIP_NONE, pos);
          } else {
            pos.setX(pos.getX() + WIN_WIDTH / 15);
            setArrowPos(SDL_FLIP_HORIZONTAL, pos);
          }
        }
        if (x == 11) {
          pos = Vector2D<int>(WIN_WIDTH / 6.5, WIN_HEIGHT - WIN_HEIGHT / 7.5);
          setArrowPos(SDL_FLIP_HORIZONTAL, pos);
        }
        if (x == 12) {
          auto image = new GameObject(
              scene, TextureManager::get("tutorial_"),
              Vector2D<int>(tutorialBackground->getPosition().getX() * 0.99,
                            tutorialBackground->getPosition().getY() +
                                tutorialBackground->getRect().h * 0.95),
              Vector2D<int>(tutorialBackground->getRect().w * 0.8,
                            tutorialBackground->getRect().h * 0.8));
          auto imageBack = new GameObject(
              scene, TextureManager::get("UI-tutorialBackground"),
              Vector2D<int>(tutorialBackground->getPosition().getX(),
                            tutorialBackground->getPosition().getY() +
                                tutorialBackground->getRect().h),
              Vector2D<int>(tutorialBackground->getRect().w,
                            tutorialBackground->getRect().h));

          addChild(imageBack);
          imageBack->addChild(image);
          pos = Vector2D<int>(imageBack->getPosition().getX() * 1.15,
                              imageBack->getPosition().getY());
          setArrowPos(SDL_FLIP_HORIZONTAL, pos);
        }
        if (x == 13) {
          getChildren()[5]->setRenderizable(false);
          getChildren()[5]->setTransparent(true);
          for (auto child : getChildren()[5]->getChildren()) {
            child->setTransparent(true);
            child->destroy();
          }
          pos = Vector2D<int>(WIN_WIDTH / 7, WIN_HEIGHT / 6);
          setArrowPos(SDL_FLIP_HORIZONTAL, pos);
        }
      },
      "Next ", "ButtonFont");
  const auto CloseButton = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(tutorialBackground->getRect().w / 4 +
                        tutorialBackground->getPosition().getX() * 0.9,
                    tutorialBackground->getPosition().getY() +
                        tutorialBackground->getRect().h / 4),
      Vector2D<int>(WIN_WIDTH / 8, WIN_HEIGHT / 20),
      [tutorialText_, this, controller, temporalController]() {
        this->setRenderizable(false);
        this->setTransparent(true);
        for (auto child : getChildren()) {
          child->setRenderizable(false);
          child->setTransparent(true);
        }
        controller->setTutorialDone(true);
        temporalController->setTutorialDone(true);
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

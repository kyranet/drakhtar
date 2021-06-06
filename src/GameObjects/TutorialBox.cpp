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
  auto tutorialText_ = new TutorialText(scene, rect);
  tutorialText_->setTransparent(true);

  auto arrow = new GameObject(scene, TextureManager::get("UI-arrowAnim"),
                              Vector2D<int>(400, 400),
                              Vector2D<int>(WIN_WIDTH / 20, WIN_WIDTH / 20));

  arrow->getTexture()->setFlip(SDL_FLIP_HORIZONTAL);

  const auto tutorialBackground = new GameObject(
      scene, TextureManager::get("UI-tutorialBackground"),
      {static_cast<int>(rect.x), static_cast<int>(rect.y * 1.1)},
      {static_cast<int>(rect.w * 1.3), static_cast<int>(rect.h * 1.3)});

  const auto nextButton = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(static_cast<int>(tutorialBackground->getPosition().getX() -
                                     tutorialBackground->getRect().w / 4.8),
                    tutorialBackground->getPosition().getY() +
                        tutorialBackground->getRect().h / 4),
      Vector2D<int>(WIN_WIDTH / 10, WIN_HEIGHT / 16),
      [tutorialText_, this, tutorialBackground, scene, controller]() {
        if (!tutorialText_->getClosed(tutorialText_->getCont() + 1)) {
          setNextButtonRender(false);
          setCloseButtonRender(true);
        }
        if (!tutorialText_->addCount()) {
          this->setRenderable(false);
          this->setTransparent(true);
          for (auto child : getChildren()) {
            child->setRenderable(false);
            child->setTransparent(true);
          }
        }
        Vector2D<int> pos = {0, 0};
        int x = tutorialText_->getCont();
        if (x == 9) {
          setArrowRenderizable(true);
          pos = {static_cast<int>(WIN_WIDTH - WIN_WIDTH / 1.8),
                 static_cast<int>(WIN_HEIGHT - WIN_HEIGHT / 13)};
          setArrowPos(SDL_FLIP_NONE, pos);
        }
        if (x == 10) {
          if (controller->getActiveUnit() != nullptr)
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
          auto image = new GameObject(
              scene, TextureManager::get("tutorial_"),
              {static_cast<int>(tutorialBackground->getPosition().getX() *
                                0.99),
               static_cast<int>(tutorialBackground->getPosition().getY() +
                                tutorialBackground->getRect().h * 0.95)},
              {static_cast<int>(tutorialBackground->getRect().w * 0.8),
               static_cast<int>(tutorialBackground->getRect().h * 0.8)});
          auto imageBack = new GameObject(
              scene, TextureManager::get("UI-tutorialBackground"),
              Vector2D<int>(tutorialBackground->getPosition().getX(),
                            tutorialBackground->getPosition().getY() +
                                tutorialBackground->getRect().h),
              Vector2D<int>(tutorialBackground->getRect().w,
                            tutorialBackground->getRect().h));

          addChild(imageBack);
          imageBack->addChild(image);
          pos = {static_cast<int>(imageBack->getPosition().getX() * 1.15),
                 imageBack->getPosition().getY()};
          setArrowPos(SDL_FLIP_HORIZONTAL, pos);
        }
        if (x == 13) {
          pos = {static_cast<int>(WIN_WIDTH / 6.5),
                 static_cast<int>(WIN_HEIGHT - WIN_HEIGHT / 7.5)};
          setArrowPos(SDL_FLIP_HORIZONTAL, pos);
        }
        if (x == 14) {
          getChildren()[5]->setRenderable(false);
          getChildren()[5]->setTransparent(true);
          for (auto child : getChildren()[5]->getChildren()) {
            child->setTransparent(true);
            child->destroy();
          }
          pos = {static_cast<int>(WIN_WIDTH / 7),
                 static_cast<int>(WIN_HEIGHT / 6)};
          setArrowPos(SDL_FLIP_HORIZONTAL, pos);
        }
        if (x == 15) {
          pos = {static_cast<int>(WIN_WIDTH / 7),
                 static_cast<int>(WIN_HEIGHT / 2.5)};
          setArrowPos(SDL_FLIP_HORIZONTAL, pos);
        }
      },
      Game::getInstance()->getLocale()->format("NEXT"), "ButtonFont");
  const auto CloseButton = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(
          static_cast<int>(tutorialBackground->getRect().w / 3 +
                           tutorialBackground->getPosition().getX() * 0.93),
          tutorialBackground->getPosition().getY() +
              tutorialBackground->getRect().h / 4),
      Vector2D<int>(WIN_WIDTH / 10, WIN_HEIGHT / 16),
      [tutorialText_, this, controller, temporalController]() {
        this->setRenderable(false);
        this->setTransparent(true);
        for (auto child : getChildren()) {
          child->setRenderable(false);
          child->setTransparent(true);
        }
        controller->setTutorialDone(true);
        temporalController->setTutorialDone(true);
      },
      Game::getInstance()->getLocale()->format("CLOSE"), "ButtonFont");

  addChild(tutorialBackground);
  addChild(tutorialText_);
  addChild(nextButton);
  addChild(CloseButton);
  setCloseButtonRender(true);
  addChild(arrow);
  setArrowRenderizable(false);
}

void TutorialBox::setNextButtonRender(bool next) {
  getChildren()[2]->setRenderable(next);
  getChildren()[2]->setTransparent(!next);
}

void TutorialBox::setCloseButtonRender(bool close) {
  getChildren()[3]->setRenderable(close);
  getChildren()[3]->setTransparent(!close);
}

void TutorialBox::setArrowPos(SDL_RendererFlip flip, Vector2D<int> pos) {
  getChildren()[4]->setPosition(pos);
  getChildren()[4]->getTexture()->setFlip(flip);
}

void TutorialBox::setArrowRenderizable(bool renderizable) {
  getChildren()[4]->setRenderable(renderizable);
}

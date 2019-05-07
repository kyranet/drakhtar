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
    : GameObject(scene, nullptr, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                 Vector2D<int>(1, 1)) {
  SDL_Rect rect = {pos.getX(),pos.getY(),size.getX(),size.getY()};
  auto tutorialText_ = new TutorialText(scene, this, filename,rect);

  const auto tutorialBackground = new GameObject(
      scene, TextureManager::get("UI-tutorialBackground"),
                     Vector2D<int>(rect.x,rect.y*1.1),
     Vector2D<int>(rect.w * 1.3, rect.h * 1.2));
  addChild(tutorialBackground);
  const auto nextButton = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(tutorialBackground->getRect().w +
                        tutorialBackground->getPosition().getX() / 2.5,
                    tutorialBackground->getPosition().getY() / 2.5 +
                        tutorialBackground->getRect().h),
      Vector2D<int>(WIN_WIDTH / 13, WIN_HEIGHT / 19),
                 [tutorialText_,this]() {
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
                  Vector2D<int>(tutorialBackground->getRect().w +
                      tutorialBackground->getPosition().getX() / 30,
                  tutorialBackground->getPosition().getY() / 2.5 +
                      tutorialBackground->getRect().h),
                 Vector2D<int>(WIN_WIDTH / 14, WIN_HEIGHT / 20),
                 [tutorialText_,this]() { tutorialText_->closeAddCount();
        for (auto child : getChildren()) {
      child->setRenderizable(false);
          child->setTransparent(true);
        }
                 },
                 "Close ", "ButtonFont");
  
  addChild(tutorialText_);
  addChild(nextButton);
  addChild(CloseButton);
  // const auto lineJumpLimit = static_cast<int>(WIN_WIDTH * 0.4);

  /*const auto tutorialImage =
      new GameObject(scene, TextureManager::get(imageText_),
                     Vector2D<int>(posX, posY - WIN_HEIGHT / 7),
                     Vector2D<int>(640 - WIN_WIDTH / 5, 640 - WIN_HEIGHT
  / 1.65));

  const SDL_Color textColor = {255, 255, 255, 255};

  const auto tutorialTextSprite = new Text(scene_,
  FontManager::get("StatsFont"), Vector2D<int>(posX, posY - WIN_HEIGHT / 10),
      textColor, dialogText_, lineJumpLimit);

  const auto dialogueBackgroundBox = new GameObject(
      scene_, TextureManager::get("UI-tutorialBackground"),
      Vector2D<int>(posX, posY),
      Vector2D<int>(640, 480));


  const auto closeButton = new Button(
      scene_, TextureManager::get("Vanilla-Button"),
      Vector2D<int>(
          dialogueBackgroundBox->getPosition().getX() + WIN_WIDTH / 10,
          dialogueBackgroundBox->getPosition().getY() + WIN_HEIGHT / 6),
      Vector2D<int>(WIN_WIDTH / 13, WIN_HEIGHT / 19), [this]() { },
      "close", "ButtonFont");

  tutorialTextSprite->setColor(textColor);
  tutorialTextSprite->setText(dialogText_, textColor, lineJumpLimit);
  tutorialTextSprite->setPosition({posX, posY + 50});

  addChild(dialogueBackgroundBox);
  addChild(tutorialImage);
  addChild(tutorialTextSprite);
  addChild(nextButton);
  addChild(closeButton);
  dialogueBackgroundBox->addEventListener(
    new TutorialSceneOnClick(dialogueBackgroundBox));*/
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "SkillButton.h"
#include "Commanders/Commander.h"
#include "Controllers/PlayerController.h"
#include "EventListeners/SkillButtonListener.h"
#include "GameObjects/ButtonText.h"
#include "Managers/Input.h"
#include "Managers/State.h"
#include "Scenes/GameScene.h"
#include "SkillDescriptionBox.h"
#include "Structures/Texture.h"

SkillButton::SkillButton(GameScene* scene, Texture* texture,
                         Texture* disabledText, Vector2D<int> pos,
                         Vector2D<int> size, Commander* commander, int skill)
    : GameObject(scene, texture, pos, size),
      commander_(commander),
      gameScene_(scene),
      disabledText_(disabledText) {
  skill_ = commander_->getSkills().at(static_cast<uint16_t>(skill));

  skillDescriptionBox_ = new SkillDescriptionBox(scene, this);
  addChild(skillDescriptionBox_);

  hoverListener_ = new SkillButtonListener(this, skillDescriptionBox_);
  addEventListener(hoverListener_);

  buttonText_ = new ButtonText(scene, " ", "SkillButtonFont", size,
                               Vector2D<int>(pos.getX() + 3, pos.getY() - 8));
  buttonText_->setTransparent(true);
  addChild(buttonText_);
}

bool SkillButton::isActive() const {
  const auto state = reinterpret_cast<GameScene*>(getScene())->getState();
  return state->getActiveUnit() == commander_ &&
         skill_->getRemainingCooldown() == 0;
}

void SkillButton::handleEvents(SDL_Event e) {
  hoverListener_->run(e);

  // Only handle when it's a left click
  if (isActive() && e.type == SDL_MOUSEBUTTONDOWN &&
      e.button.button == SDL_BUTTON_LEFT) {
    SDL_Point p = {e.button.x, e.button.y};
    const auto rect = getRect();
    if (SDL_PointInRect(&p, &rect)) {
      skill_->cast();

      const auto player = dynamic_cast<PlayerController*>(
          gameScene_->getState()->getController());
      if (player) {
        player->highlightCells();
        if (!player->canAttack() && player->canMove() &&
            !player->canCastSkills())
          player->finish();
      }
    }
  }

  // Update button text
  int CD = skill_->getRemainingCooldown();
  if (CD <= 0) {
    buttonText_->setText(" ");
  } else {
    buttonText_->setText(std::to_string(CD));
  }
}

void SkillButton::update() {
  const auto area = getRect();
  hovered_ = Input::isMouseInside(&area);
  GameObject::update();
}

void SkillButton::render(SDL_Rect rect) const {
  if (hovered_) {
    rect = {position_.getX() - (size_.getX() + increSize_) / 2,
            position_.getY() - (size_.getY() + increSize_) / 2,
            size_.getX() + increSize_, size_.getY() + increSize_};
  }

  if (commander_->getSkills().empty()) {  // Temporary fix
    disabledText_->renderFrame(rect,
                               texture_->getAnimation()[texture_->getFrame()]);
  } else {
    // Disable button if the skill is in CD or its not the unit's turn
    if (!isActive()) {
      if (getRenderizable() && disabledText_ != nullptr) {
        disabledText_->renderFrame(
            rect, texture_->getAnimation()[texture_->getFrame()]);
      }
    } else {
      if (getRenderizable() && texture_ != nullptr) {
        texture_->renderFrame(rect,
                              texture_->getAnimation()[texture_->getFrame()]);
      }
    }

    for (auto child : children_)
      if (child->getRenderizable()) child->render();
  }
}

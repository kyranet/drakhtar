// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "SkillButton.h"

#include "../Structures/Texture.h"
#include "Commanders/Commander.h"
#include "EventListeners/SkillButtonListener.h"
#include "GameObjects/ButtonText.h"
#include "SkillDescriptionBox.h"

SkillButton::SkillButton(GameScene* scene, Texture* texture,
                         Texture* disabledText, Vector2D<int> pos,
                         Vector2D<int> size, Commander* commander, int skill)
    : GameObject(scene, texture, pos, size),
      disabledText_(disabledText),
      gameScene_(scene),
      commander_(commander) {
  skill_ = commander_->getSkills().at(skill);

  skillDescriptionBox_ = new SkillDescriptionBox(scene, this);
  addChild(skillDescriptionBox_);

  hoverListener_ = new SkillButtonListener(this, skillDescriptionBox_);
  addEventListener(hoverListener_);

  buttonText_ = new ButtonText(scene, " ", "SkillButtonFont", size,
                               Vector2D<int>(pos.getX() + 3, pos.getY() - 8));
  buttonText_->setTransparent(true);
  addChild(buttonText_);
}

void SkillButton::handleEvents(SDL_Event e) {
  hoverListener_->run(e);

  // Only handle when it's a left click
  if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
    SDL_Point p = {e.button.x, e.button.y};
    const auto rect = getRect();
    if (SDL_PointInRect(&p, &rect)) {
      skill_->cast(gameScene_);
    }
  }

  // Update button text
  int CD = skill_->getRemainingCooldown();
  if (CD == 0) {
    buttonText_->setText(" ");
  } else {
    buttonText_->setText(std::to_string(CD));
  }
}

void SkillButton::render(SDL_Rect rect) const {
  if (commander_->getSkills().size() == 0) {  // Temporary fix
    disabledText_->renderFrame(rect,
                               texture_->getAnimation()[texture_->getFrame()]);
  } else {
    // Disable button if the skill is in CD or its not the unit's turn
    if (!commander_->getMoving() || skill_->getRemainingCooldown() != 0) {
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

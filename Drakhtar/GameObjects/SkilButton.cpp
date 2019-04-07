// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "SkillButton.h"

SkillButton::SkillButton(Scene* scene, Texture* texture, Vector2D<int> pos,
                         Vector2D<int> size, Board* board, Commander* commander,
                         int skill)
    : GameObject(scene, texture, pos, size),
      board_(board),
      commander_(commander),
      skill_(skill) {}

void SkillButton::handleEvents(SDL_Event e) {
  // Only handle when it's a left click
  if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
    SDL_Point p = {e.button.x, e.button.y};
    if (SDL_PointInRect(&p, &getRect())) {
      commander_->getSkills().at(skill_)->cast(board_);
    }
  }
}

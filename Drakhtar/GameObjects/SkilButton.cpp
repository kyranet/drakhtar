// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "SkillButton.h"

SkillButton::SkillButton(Scene *scene, Texture *texture, Vector2D<int> pos,
                         Vector2D<int> size, Board *board, Commander *commander,
                         int skill)
    : GameObject(scene, texture, pos, size), commander_(commander),
      skill_(skill), board_(board) {}

void SkillButton::handleEvents(SDL_Event e) {
  // Only handle when it's a left click
  if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
    SDL_Point p = {e.button.x, e.button.y};
    const auto rect = getRect();
    if (SDL_PointInRect(&p, &rect)) {
      commander_->getSkills().at(skill_)->cast(board_);
    }
  }
}

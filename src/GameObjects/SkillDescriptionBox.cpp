// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
#include "SkillDescriptionBox.h"

#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Utils/Constants.h"
#include "Skill.h"
#include "SkillButton.h"
#include "Text.h"

SkillDescriptionBox::SkillDescriptionBox(Scene* scene, SkillButton* skillButton)
    : GameObject(
          scene, TextureManager::get("Reward-Panel"),
          {skillButton->getPosition().getX() +
               static_cast<int>(WIN_WIDTH / 3.4),
           skillButton->getPosition().getY() +
               static_cast<int>(WIN_HEIGHT / 10)},
          {static_cast<int>(WIN_WIDTH / 2), static_cast<int>(WIN_HEIGHT / 3)}),
      skillButton_(skillButton) {
  setTransparent(true);
  setRenderable(false);

  std::string statText_ = fillText();
  const auto skillTextSprite = new Text(
      scene_, FontManager::get("StatsFont"),
      Vector2D<int>(this->getPosition().getX(), this->getPosition().getY()),
      {0, 0, 0, 1}, statText_, static_cast<int>(getRect().w * 0.8));
  addChild(skillTextSprite);
  skillTextSprite->setTransparent(true);
  active_ = true;
}

void SkillDescriptionBox::render() const {
  if (active_) {
    GameObject::render();
  }
}

std::string SkillDescriptionBox::fillText() const {
  const auto skill = skillButton_->getSkill();
  const auto description = skill->getDescription();
  auto text = "<" + skill->getId() + ">\n";
  text += description + "\n";
  return text;
}

void SkillDescriptionBox::updateText() const { fillText(); }

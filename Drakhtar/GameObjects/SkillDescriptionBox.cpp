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
          Vector2D<int>(skillButton->getPosition().getX() + WIN_WIDTH / 3.4,
                        skillButton->getPosition().getY() + WIN_HEIGHT / 10),
          Vector2D<int>(static_cast<int>(WIN_WIDTH / 2),
                        static_cast<int>(WIN_HEIGHT / 3))),
      skillButton_(skillButton) {
  Vector2D<int> pos = skillButton_->getPosition();

  std::string statText_ = fillText();
  const auto statTextSprite = new Text(
      scene_, FontManager::get("StatsFont"),
      Vector2D<int>(this->getPosition().getX(), this->getPosition().getY()),
      {0, 0, 0, 1}, statText_, this->getRect().w * 0.9);
  addChild(statTextSprite);
  active_ = true;
}

void SkillDescriptionBox::render() const {
  if (active_) {
    GameObject::render();
  }
}

std::string SkillDescriptionBox::fillText() {
  Skill* skill = skillButton_->getSkill();
  std::string description = skill->getDescription();
  std::string text = "<" + skill->getId() + ">\n";
  text += description + "\n";
  return text;
}

void SkillDescriptionBox::updateText() { fillText(); }

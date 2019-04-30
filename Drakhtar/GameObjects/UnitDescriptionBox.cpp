// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
#include "UnitDescriptionBox.h"

#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Utils/Constants.h"
#include "Skill.h"
#include "Text.h"
#include "Unit.h"

UnitDescriptionBox::UnitDescriptionBox(Scene* scene, Unit* unit)
    : GameObject(scene, TextureManager::get("Reward-Panel"),
                 Vector2D<int>(0, 0),
                 Vector2D<int>(130, 110)),
      unit_(unit) {
  setTransparent(true);
  setRenderizable(false);
  Vector2D<int> pos = unit_->getPosition();

  std::string statText_ = fillText();
  skillTextSprite_ = new Text(
      scene_, FontManager::get("TutorialFont"),
      Vector2D<int>(this->getPosition().getX() + 5, this->getPosition().getY()),
      {0, 0, 0, 1}, statText_, this->getRect().w * 0.9);
  addChild(skillTextSprite_);
  skillTextSprite_->setTransparent(true);
  active_ = true;
}

void UnitDescriptionBox::render() const {
  if (active_) {
    SDL_Rect rect = {unit_->getPosition().getX(), unit_->getPosition().getY(),
                     130, 110};
    
    if (getRenderizable() && texture_ != nullptr) {
      texture_->renderFrame(rect,
                            texture_->getAnimation()[texture_->getFrame()]);
    }
    skillTextSprite_->render(
        {unit_->getPosition().getX() + 15, unit_->getPosition().getY() + 5, 110, 100});
  }
}

std::string UnitDescriptionBox::fillText() const {
  auto text = "< " + unit_->getType() + " >\n";
  text += "Attack: " + std::to_string(unit_->getBaseStats().attack) + " (" +
          std::to_string(unit_->getStats().attack) + ")\n";
  text += "Defense: " + std::to_string(unit_->getStats().defense) + "%\n";
  text += "Range: " + std::to_string(unit_->getStats().attackRange) + "\n";
  text += "Move: " + std::to_string(unit_->getStats().moveRange) + "\n";
  text += "Speed: " + std::to_string(unit_->getStats().speed) + "\n";
  return text;
}

void UnitDescriptionBox::updateText() const { fillText(); }

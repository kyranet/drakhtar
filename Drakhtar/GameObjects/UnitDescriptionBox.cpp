// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
#include "UnitDescriptionBox.h"

#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Utils/Constants.h"
#include "Board.h"
#include "EventListeners/StatBoxListener.h"
#include "Managers/Input.h"
#include "Skill.h"
#include "Text.h"
#include "Unit.h"
#include "Structures/Team.h"
#include "Controllers/UnitsController.h"

UnitDescriptionBox::UnitDescriptionBox(Scene* scene, Board* board)
    : GameObject(scene, TextureManager::get("Reward-Panel"),
                 Vector2D<int>(500, 500), Vector2D<int>(130, 110)) {
  setTransparent(true);
  setRenderizable(false);

  listener_ = new StatBoxListener(board, this);
  board->addEventListener(listener_);

  unitStatsText_ = new Text(
      scene_, FontManager::get("TutorialFont"),
      Vector2D<int>(this->getPosition().getX() + 5, this->getPosition().getY()),
      {0, 0, 0, 1}, " ", this->getRect().w * 0.9);
  addChild(unitStatsText_);
  unitStatsText_->setTransparent(true);

  unitDamageText_ = new Text(
      scene_, FontManager::get("TutorialFont"),
      Vector2D<int>(this->getPosition().getX() + 5, this->getPosition().getY() + 50),
      {255, 0, 0, 1}, " ", this->getRect().w * 0.9);
  addChild(unitDamageText_);
  unitDamageText_->setTransparent(true);

  active_ = true;
}

void UnitDescriptionBox::render() const {
  if (active_) {
    SDL_Rect rect = {Input::getMousePosition().getX(),
                     Input::getMousePosition().getY(), 130, 110};

    if (getRenderizable() && texture_ != nullptr) {
      texture_->renderFrame(rect,
                            texture_->getAnimation()[texture_->getFrame()]);
    }
    unitStatsText_->render(rect);
    unitDamageText_->render(rect);
  }
}
/*
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
*/
void UnitDescriptionBox::updateText(Unit* unit) const {
  Unit* activeUnit = unit->getTeam()->getController()->getActiveUnit();
  std::string text = "< " + unit->getType() + " >\n";
  text += "Attack: " + std::to_string(unit->getBaseStats().attack) + " (" +
          std::to_string(unit->getStats().attack) + ")\n";
  text += "Defense: " + std::to_string(unit->getStats().defense) + "%\n";
  text += "Range: " + std::to_string(unit->getStats().attackRange) + "\n";
  text += "Move: " + std::to_string(unit->getStats().moveRange) + "\n";
  text += "Speed: " + std::to_string(unit->getStats().speed) + "\n";

  unitStatsText_->setText(text);

  unitDamageText_->setText("TEST");
}

void UnitDescriptionBox::show() {
  setRenderizable(true);
  unitStatsText_->setRenderizable(true);
}

void UnitDescriptionBox::hide() {
  setRenderizable(false);
  unitStatsText_->setRenderizable(false);
}

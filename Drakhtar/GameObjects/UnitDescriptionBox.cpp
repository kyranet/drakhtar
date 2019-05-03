// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
#include "UnitDescriptionBox.h"

#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Utils/Constants.h"
#include "Board.h"
#include "Controllers/UnitsController.h"
#include "EventListeners/StatBoxListener.h"
#include "Managers/Input.h"
#include "Managers/TurnManager.h"
#include "Skill.h"
#include "Structures/Team.h"
#include "Text.h"
#include "Unit.h"

UnitDescriptionBox::UnitDescriptionBox(Scene* scene, Board* board,
                                       TurnManager* turnManager)
    : GameObject(scene, TextureManager::get("Reward-Panel"),
                 Vector2D<int>(0, 0), Vector2D<int>(0, 0)),
      board_(board), turnManager_(turnManager) {
  setTransparent(true);
  setRenderizable(false);

  const auto listener = new StatBoxListener(board, this);
  board->addEventListener(listener);

  unitStatsText_ = new Text(
      scene_, FontManager::get("TutorialFont"),
      Vector2D<int>(this->getPosition().getX() + 5, this->getPosition().getY()),
      {0, 0, 0, 1}, " ", this->getRect().w * 0.9);
  addChild(unitStatsText_);
  unitStatsText_->setTransparent(true);

  unitDamageText_ = new Text(scene_, FontManager::get("TutorialFont"),
                             Vector2D<int>(this->getPosition().getX() + 5,
                                           this->getPosition().getY() + 50),
                             {255, 0, 0, 1}, " ", this->getRect().w * 0.9);
  addChild(unitDamageText_);
  unitDamageText_->setTransparent(true);
  active_ = true;
}

void UnitDescriptionBox::render() const {
  if (active_) {
    if (getRenderizable() && texture_ != nullptr) {
      // Stats box
      texture_->renderFrame({Input::getMousePosition().getX(),
                             Input::getMousePosition().getY(), 140, 130},
                            texture_->getAnimation()[texture_->getFrame()]);
      unitStatsText_->render({Input::getMousePosition().getX() + 15,
                              Input::getMousePosition().getY() + 10, 260, 110});

      // Attack damage box
      if (showDamage_) {
        texture_->renderFrame({Input::getMousePosition().getX(),
                               Input::getMousePosition().getY() + 130, 180, 80},
                              texture_->getAnimation()[texture_->getFrame()]);
        unitDamageText_->render({Input::getMousePosition().getX() + 15,
                                 Input::getMousePosition().getY() + 140, 250,
                                 60});
      }
    }
  }
}

void UnitDescriptionBox::updateText(Unit* unit) {
  std::string text = "<" + unit->getType() + ">\n";
  text += "Attack: " + std::to_string(unit->getBaseStats().attack) + " (" +
          std::to_string(unit->getStats().attack) + ")\n";
  text += "Defense: " + std::to_string(unit->getStats().defense) + "%\n";
  text += "Range: " + std::to_string(unit->getStats().attackRange) + "\n";
  text += "Move: " + std::to_string(unit->getStats().moveRange) + "\n";
  text += "Speed: " + std::to_string(unit->getStats().speed) + "\n";

  unitStatsText_->setText(text);

  Unit* activeUnit = turnManager_->getActiveUnit();

  showDamage_ = board_->isInRange(activeUnit->getBox(), unit->getBox(),
                                 activeUnit->getStats().attackRange) &&
               unit->getTeam() != activeUnit->getTeam();

  int damage = static_cast<int>(activeUnit->getStats().attack *
                                (1.0 - unit->getStats().defense / 100.0));
  text =
      "Unit's attack: " + std::to_string(activeUnit->getStats().attack) + ")\n";
  text +=
      "Enemy's defense: " + std::to_string(unit->getStats().defense) + "%\n";
  text += "Final damage: " + std::to_string(damage);
  unitDamageText_->setText(text);
}

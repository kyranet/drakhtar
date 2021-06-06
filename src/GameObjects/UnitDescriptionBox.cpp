// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
#include "UnitDescriptionBox.h"

#include "Board.h"
#include "Controllers/UnitsController.h"
#include "EventListeners/StatBoxListener.h"
#include "GameObjects/Box.h"
#include "Managers/FontManager.h"
#include "Managers/Input.h"
#include "Managers/State.h"
#include "Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Skill.h"
#include "Structures/Game.h"
#include "Structures/Team.h"
#include "Text.h"
#include "Unit.h"
#include "Utils/Constants.h"

UnitDescriptionBox::UnitDescriptionBox(Scene* scene, Board* board)
    : GameObject(scene, TextureManager::get("Reward-Panel"),
                 Vector2D<int>(0, 0), Vector2D<int>(0, 0)),
      board_(board),
      showDamage_(false) {
  setTransparent(true);
  setRenderable(false);

  const auto listener = new StatBoxListener(board, this);
  board->addEventListener(listener);

  unitStatsText_ =
      new Text(scene_, FontManager::get("TutorialFont"),
               Vector2D<int>(getPosition().getX() + 5, getPosition().getY()),
               {0, 0, 0, 1}, " ", static_cast<int>(getRect().w * 0.9));
  addChild(unitStatsText_);
  unitStatsText_->setTransparent(true);

  unitDamageText_ =
      new Text(scene_, FontManager::get("TutorialFont"),
               {getPosition().getX() + 5, getPosition().getY() + 50},
               {255, 0, 0, 1}, " ", static_cast<int>(getRect().w * 0.9));
  addChild(unitDamageText_);
  unitDamageText_->setTransparent(true);
  active_ = true;
}

void UnitDescriptionBox::render() const {
  if (active_) {
    if (getRenderable() && texture_ != nullptr) {
      // Stats box
      texture_->renderFrame({Input::getMousePosition().getX(),
                             Input::getMousePosition().getY(), 150, 130},
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
  const auto scene = reinterpret_cast<GameScene*>(getScene());
  const auto state = scene->getState();
  const auto stats = state->getModifiedAt(unit->getBox()->getIndex());

  std::string text = "<" + unit->getType() + ">\n";
  text += Game::getInstance()->getLocale()->format("ATTACK") + ": " +
          std::to_string(unit->getBaseStats().attack) + " (" +
          std::to_string(stats.attack_) + ")\n";
  text += Game::getInstance()->getLocale()->format("DEFENSE") + ": " +
          std::to_string(stats.defense_) + "%\n";
  text += Game::getInstance()->getLocale()->format("RANGE") + ": " +
          std::to_string(stats.attackRange_) + "\n";
  text += Game::getInstance()->getLocale()->format("MOVE") + ": " +
          std::to_string(stats.moveRange_) + "\n";
  text += Game::getInstance()->getLocale()->format("SPEED") + ": " +
          std::to_string(stats.speed_) + "\n";

  unitStatsText_->setText(text);

  Unit* activeUnit = state->getActiveUnit();

  const auto enemyStats = state->getModifiedAt(unit->getBox()->getIndex());

  showDamage_ =
      unit->getTeam() != activeUnit->getTeam() &&
      state->isInRange(activeUnit->getBox()->getIndex(),
                       unit->getBox()->getIndex(), stats.attackRange_);

  int damage =
      static_cast<int>(stats.attack_ * (1.0 - enemyStats.defense_ / 100.0));
  text = Game::getInstance()->getLocale()->format("UNITATTACK") +
         std::to_string(stats.attack_) + "\n";
  text += Game::getInstance()->getLocale()->format("ENEMYDEFENSE") +
          std::to_string(enemyStats.defense_) + "%\n";
  text += Game::getInstance()->getLocale()->format("FINALDAMAGE") +
          std::to_string(damage);
  unitDamageText_->setText(text);
}

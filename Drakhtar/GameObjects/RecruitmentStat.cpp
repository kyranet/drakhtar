// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
#include "RecruitmentStat.h"

#include "../Managers/FontManager.h"
#include "../Managers/GameManager.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Structures/Font.h"
#include "../Utils/Constants.h"
#include "../Utils/Vector2D.h"
#include "GameObjects/Button.h"
#include "GameObjects/Unit.h"
#include "Structures/Game.h"
#include "Structures/UnitFactory.h"
#include "Text.h"

RecruitmentStat::RecruitmentStat(Scene* scene, StoreUnit* controller)
    : GameObject(scene, TextureManager::get("Reward-Panel"),
                 Vector2D<int>(WIN_WIDTH * 0.68, WIN_HEIGHT * 0.25),
                 Vector2D<int>(WIN_WIDTH * 0.40, WIN_HEIGHT * 0.45)),
      currentSelected_(controller) {
  auto pos = currentSelected_->unit->getPosition();

  std::string statText_ = fillText();
  const auto statTextSprite =
      new Text(scene_, FontManager::get("StatsFont"),
               Vector2D<int>(this->getPosition().getX() + WIN_WIDTH * 0.04,
                             this->getPosition().getY()),
               {0, 0, 0, 1}, statText_, this->getRect().w * 0.9);
  addChild(statTextSprite);
  active_ = true;
}

void RecruitmentStat::render() const {
  if (active_) {
    GameObject::render();
  }
}

std::string RecruitmentStat::fillText() {
  std::string text = "<" + currentSelected_->type + ">\n";
  auto map = GameManager::getInstance()->getArmy();
  auto stats = UnitFactory(Game::getSceneMachine()->getCurrentScene())
                   .getStats(currentSelected_->type);
  text += "Total amount: " + std::to_string(map[currentSelected_->type]) + "\n";
  text += "Attack-> " + std::to_string(stats.attack) + " (" +
          std::to_string(stats.attack * map[currentSelected_->type]) + ")\n";
  text += "Defense-> " + std::to_string(stats.defense) + "%\n";
  text += "Speed-> " + std::to_string(stats.speed) + "\n";
  text += "Attack range-> " + std::to_string(stats.attackRange) + "\n";
  text += "Move range-> " + std::to_string(stats.moveRange) + "\n";
  text += "Prize-> " + std::to_string(stats.prize * 2) + "\n";
  return text;
}

std::string RecruitmentStat::infoFillText() {
  std::string info = "-The total amount  you buy will be added to ONE unit";
  return info;
}

void RecruitmentStat::updateText() { fillText(); }

RecruitmentStat::~RecruitmentStat() {}

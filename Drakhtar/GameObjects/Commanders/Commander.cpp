// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Commander.h"

#include "../../GameObjects/Board.h"
#include "../../GameObjects/Box.h"
#include "../../Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Structures/Game.h"
#include "Structures/Team.h"

Commander::Commander(const std::string& name, Scene* scene, Texture* texture, Box* box,
                     UnitStats commanderStats)
    : Unit(scene, texture, box, commanderStats, name) {
  isCommander_ = true;
}

Commander::~Commander() {
  for (auto skill : skills_) {
    delete skill;
  }
  skills_.clear();
}

void Commander::kill() {
  Unit::kill();
  reinterpret_cast<GameScene*>(getScene())
      ->gameOver(!(getTeam()->getColor() == Color::BLUE));
}

void Commander::moveToBox(Box* box) {
  Unit::moveToBox(box);
  const auto rect = box_->getRect();
  commanderIcon_->setPosition(
      Vector2D<int>(rect.x, static_cast<int>(rect.y + rect.h / 1.31)));
}

void Commander::setCommanderHealthBar() {
  const auto rect = box_->getRect();

  commanderIcon_ = new GameObject(
      scene_, TextureManager::get("UI-commanderIcon"),
      Vector2D<int>(rect.x, static_cast<int>(rect.y + rect.h / 1.15)),
      Vector2D<int>(rect.h / 2, rect.h / 2));

  commanderIcon_->setTransparent(true);
  addChild(commanderIcon_);
}

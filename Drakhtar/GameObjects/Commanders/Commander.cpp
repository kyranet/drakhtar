// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Commander.h"

#include "../../GameObjects/Board.h"
#include "../../GameObjects/Box.h"
#include "../../Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Scenes/TransitionScene.h"
#include "Structures/Game.h"
#include "Structures/Team.h"

Commander::Commander(Scene* scene, Texture* texture, Box* box,
                     const UnitStats commanderStats)
    : Unit(scene, texture, box, commanderStats, "") {
  const auto rect = box_->getRect();

  commanderIcon_ =
      new GameObject(scene, TextureManager::get("UI-commanderIcon"),
                     Vector2D<int>(rect.x, rect.y - rect.h / 3),
                     Vector2D<int>(rect.h / 2, rect.h / 2));

  addChild(commanderIcon_);
}

Commander::~Commander() {
  for (auto skill : skills_) {
    delete skill;
  }
  skills_.clear();
}

void Commander::onSelect() {
  Unit::onSelect();
  for (auto skill : skills_) {
    // Lowers skill cooldown timer
    if (skill->getRemainingCooldown() > 0) {
      skill->setRemainingCooldown(skill->getRemainingCooldown() - 1);
    }

    // Lowers skill duration timer
    if (skill->getRemainingDuration() > 0) {
      skill->setRemainingDuration(skill->getRemainingDuration() - 1);
    }

    // Ends skill if it was active and its duration finished
    if (skill->getActive() && skill->getRemainingDuration() == 0) {
      skill->end();
    }
  }
}

void Commander::onDeselect() {
  Unit::onDeselect();

  for (auto skill : skills_) {
    // Ends skill if it was active and its duration finished
    if (skill->getActive() && skill->getRemainingDuration() == 0) {
      skill->end();
    }
  }
}

void Commander::kill() {
  Unit::kill();
  int currentScene = reinterpret_cast<GameScene*>(getScene())->getBattleInd();
  if (getTeam()->getColor() == Color::BLUE) {
    Game::getSceneMachine()->changeScene(new GameScene(currentScene));
  } else {
    auto scene = reinterpret_cast<GameScene*>(
        Game::getSceneMachine()->getCurrentScene());
    scene->addPrize(baseStats_.prize);
    scene->saveStatus();
    Game::getSceneMachine()->changeScene(new TransitionScene(currentScene + 1));
  }
}

void Commander::moveToBox(Box* box) {
  Unit::moveToBox(box);
  const auto rect = box_->getRect();
  commanderIcon_->setPosition(Vector2D<int>(rect.x, rect.y - rect.h / 3));
}

void Commander::attack(Unit* enemy, bool allowsCounter) {
  // If the attack would allow a counter but the commander is unstoppable_, the
  // attack does not allow counter
  if (allowsCounter && unstoppable_) {
    allowsCounter = false;
  }
  Unit::attack(enemy, allowsCounter);
}

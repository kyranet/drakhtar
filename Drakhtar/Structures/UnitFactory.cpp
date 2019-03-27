// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitFactory.h"
#include "../GameObjects/Battalion.h"
#include "../GameObjects/Unit.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "Team.h"

UnitFactory::UnitFactory(Scene *scene) : scene_(scene) {}

UnitFactory::~UnitFactory() = default;

Unit *UnitFactory::newSoldier(Team *team, Box *box, const int size) const {
  const auto soldierAttack = 5;
  const auto soldierDefense = 5;
  const auto soldierHealth = 10;
  const auto soldierAttackRange = 1;
  const auto soldierMoveRange = 3;
  const auto soldierSpeed = 3;
  const auto soldierPrize = 3;

  const auto textureName =
      team->getColor() == BLUE ? "Units-BlueSoldier" : "Units-RedSoldier";

  const auto unit =
      new Battalion(scene_, TextureManager::get(textureName), box,
                    soldierAttack, soldierDefense, soldierHealth, soldierSpeed,
                    soldierAttackRange, soldierMoveRange, size, soldierPrize);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newArcher(Team *team, Box *box, const int size) const {
  const auto archerAttack = 6;
  const auto archerDefense = 3;
  const auto archerHealth = 10;
  const auto archerAttackRange = 3;
  const auto archerMoveRange = 1;
  const auto archerSpeed = 3;
  const auto archerPrize = 3;

  const auto textureName =
      team->getColor() == BLUE ? "Units-BlueArcher" : "Units-RedArcher";

  const auto unit =
      new Battalion(scene_, TextureManager::get(textureName), box, archerAttack,
                    archerDefense, archerHealth, archerSpeed, archerAttackRange,
                    archerMoveRange, size, archerPrize);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newKnight(Team *team, Box *box, const int size) const {
  const auto knightAttack = 8;
  const auto knightDefense = 7;
  const auto knightHealth = 15;
  const auto knightAttackRange = 1;
  const auto knightMoveRange = 5;
  const auto knightSpeed = 5;
  const auto knightPrize = 8;

  const auto textureName =
      team->getColor() == BLUE ? "Units-BlueKnight" : "Units-RedKnight";

  const auto unit =
      new Battalion(scene_, TextureManager::get(textureName), box, knightAttack,
                    knightDefense, knightHealth, knightSpeed, knightAttackRange,
                    knightMoveRange, size, knightPrize);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newWizard(Team *team, Box *box, const int size) const {
  const auto wizardAttack = 4;
  const auto wizardDefense = 2;
  const auto wizardHealth = 7;
  const auto wizardAttackRange = 2;
  const auto wizardMoveRange = 1;
  const auto wizardSpeed = 2;
  const auto wizardPrize = 5;

  const auto textureName =
      team->getColor() == BLUE ? "Units-BlueMage" : "Units-RedMage";

  const auto unit =
      new Battalion(scene_, TextureManager::get(textureName), box, wizardAttack,
                    wizardDefense, wizardHealth, wizardSpeed, wizardAttackRange,
                    wizardMoveRange, size, wizardPrize);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newMonster(Team *team, Box *box, const int size) const {
  const auto monsterAttack = 9;
  const auto monsterDefense = 8;
  const auto monsterHealth = 15;
  const auto monsterAttackRange = 1;
  const auto monsterMoveRange = 5;
  const auto monsterSpeed = 1;
  const auto monsterPrize = 10;

  const auto textureName =
      team->getColor() == BLUE ? "Units-BlueMonster" : "Units-RedMonster";

  const auto unit =
      new Battalion(scene_, TextureManager::get(textureName), box,
                    monsterAttack, monsterDefense, monsterHealth, monsterSpeed,
                    monsterAttackRange, monsterMoveRange, size, monsterPrize);
  team->addUnit(unit);
  return unit;
}

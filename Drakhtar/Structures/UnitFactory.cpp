// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitFactory.h"
#include "../GameObjects/Battalion.h"
#include "../GameObjects/Unit.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "Team.h"

UnitFactory::UnitFactory(Scene *scene) : scene_(scene) {}

UnitFactory::~UnitFactory() {}

Unit *UnitFactory::newSoldier(Team *team, Box *box, int size) {
  int soldierAttack = 5;
  int soldierDefense = 5;
  int soldierHealth = 10;
  int soldierAttackRange = 1;
  int soldierMoveRange = 3;
  int soldierSpeed = 3;
  int soldierPrize = 3;

  string textureName = team->getColor() == Color::BLUE ? "Units-BlueSoldier"
                                                       : "Units-RedSoldier";

  auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                            soldierAttack, soldierDefense, soldierHealth, soldierSpeed,
                            soldierAttackRange, soldierMoveRange, size, soldierPrize);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newArcher(Team *team, Box *box, int size) {
  int archerAttack = 6;
  int archerDefense = 3;
  int archerHealth = 10;
  int archerAttackRange = 3;
  int archerMoveRange = 1;
  int archerSpeed = 3;
  int archerPrize = 3;

  string textureName =
      team->getColor() == Color::BLUE ? "Units-BlueArcher" : "Units-RedArcher";

  auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                            archerAttack, archerDefense, archerHealth, archerSpeed,
                            archerAttackRange, archerMoveRange, size, archerPrize);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newKnight(Team *team, Box *box, int size) {
  int knightAttack = 8;
  int knightDefense = 7;
  int knightHealth = 15;
  int knightAttackRange = 1;
  int knightMoveRange = 5;
  int knightSpeed = 5;
  int knightPrize = 8;

  string textureName =
      team->getColor() == Color::BLUE ? "Units-BlueKnight" : "Units-RedKnight";

  auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                            knightAttack, knightDefense, knightHealth, knightSpeed,
                            knightAttackRange, knightMoveRange, size, knightPrize);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newWizard(Team *team, Box *box, int size) {
  int wizardAttack = 4;
  int wizardDefense = 2;
  int wizardHealth = 7;
  int wizardAttackRange = 2;
  int wizardMoveRange = 1;
  int wizardSpeed = 2;
  int wizardPrize = 5;

  string textureName =
      team->getColor() == Color::BLUE ? "Units-BlueMage" : "Units-RedMage";

  auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                            wizardAttack, wizardDefense, wizardHealth, wizardSpeed,
                            wizardAttackRange, wizardMoveRange, size, wizardPrize);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newMonster(Team *team, Box *box, int size) {
  int monsterAttack = 9;
  int monsterDefense = 8;
  int monsterHealth = 15;
  int monsterAttackRange = 1;
  int monsterMoveRange = 5;
  int monsterSpeed = 1;
  int monsterPrize = 10;

  string textureName = team->getColor() == Color::BLUE ? "Units-BlueMonster"
                                                       : "Units-RedMonster";

  auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                            monsterAttack, monsterDefense, monsterHealth, monsterSpeed,
                            monsterAttackRange, monsterMoveRange, size, monsterPrize);
  team->addUnit(unit);
  return unit;
}

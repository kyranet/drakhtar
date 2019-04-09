// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitFactory.h"
#include "../GameObjects/Battalion.h"
#include "../GameObjects/Commanders/Thassa.h"
#include "../GameObjects/Commanders/Zamdran.h"
#include "../GameObjects/Unit.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Utils/Constants.h"
#include "Team.h"

UnitFactory::UnitFactory(Scene *scene) : scene_(scene) {}

UnitFactory::~UnitFactory() = default;

Unit *UnitFactory::newSoldier(Team *team, Box *box, const int size) const {

  UnitStats soldierStats_ = {
      soldierAttack,    soldierDefense, soldierHealth,      soldierAttackRange,
      soldierMoveRange, soldierSpeed,   soldierPrize * size};
  const auto textureName =
      team->getColor() == BLUE ? "Units-BlueSoldier" : "Units-RedSoldier";

  const auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                                  soldierStats_, "Soldier", size);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newArcher(Team *team, Box *box, const int size) const {
  UnitStats archerStats_ = {archerAttack,      archerDefense,   archerHealth,
                            archerAttackRange, archerMoveRange, archerSpeed,
                            archerPrize * size};
  const auto textureName =
      team->getColor() == BLUE ? "Units-BlueArcher" : "Units-RedArcher";

  const auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                                  archerStats_, "Archer", size);
  unit->setTeam(team);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newKnight(Team *team, Box *box, const int size) const {
  UnitStats knightStats_ = {knightAttack,      knightDefense,   knightHealth,
                            knightAttackRange, knightMoveRange, knightSpeed,
                            knightPrize * size};

  const auto textureName =
      team->getColor() == BLUE ? "Units-BlueKnight" : "Units-RedKnight";

  const auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                                  knightStats_, "Knight", size);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newWizard(Team *team, Box *box, const int size) const {

  UnitStats wizardStats_ = {wizardAttack,      wizardDefense,   wizardHealth,
                            wizardAttackRange, wizardMoveRange, wizardSpeed,
                            wizardPrize * size};
  const auto textureName =
      team->getColor() == BLUE ? "Units-BlueMage" : "Units-RedMage";

  const auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                                  wizardStats_, "Mage", size);
  team->addUnit(unit);
  return unit;
}

Unit *UnitFactory::newMonster(Team *team, Box *box, const int size) const {

  UnitStats monsterStats_ = {
      monsterAttack,    monsterDefense, monsterHealth,      monsterAttackRange,
      monsterMoveRange, monsterSpeed,   monsterPrize * size};

  const auto textureName =
      team->getColor() == BLUE ? "Units-BlueMonster" : "Units-RedMonster";

  const auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                                  monsterStats_, "Monster", size);
  team->addUnit(unit);
  return unit;
}

//---------- COMMANDERS ----------

Thassa *UnitFactory::newThassa(Team *team, Box *box) const {
  UnitStats thassaStats_ = {thassaAttack,      thassaDefense,   thassaHealth,
                            thassaAttackRange, thassaMoveRange, thassaSpeed,
                            thassaPrize};

  const auto textureName = "Units-Thassa";

  const auto unit =
      new Thassa(scene_, TextureManager::get(textureName), box, thassaStats_);
  team->addUnit(unit);
  return unit;
}

Zamdran *UnitFactory::newZamdran(Team *team, Box *box) const {
  UnitStats zamdranStats_ = {
      zamdranAttack,    zamdranDefense, zamdranHealth, zamdranAttackRange,
      zamdranMoveRange, zamdranSpeed,   zamdranPrize};
  const auto textureName = "Units-Zamdran";

  const auto unit =
      new Zamdran(scene_, TextureManager::get(textureName), box, zamdranStats_);
  team->addUnit(unit);
  return unit;
}

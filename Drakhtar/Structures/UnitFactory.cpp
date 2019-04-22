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

UnitFactory::UnitFactory(Scene* scene) : scene_(scene) {
  statMap["Soldier"] = {soldierAttack,      soldierDefense,   soldierHealth,
                        soldierAttackRange, soldierMoveRange, soldierSpeed,
                        soldierPrize};

  statMap["Archer"] = {archerAttack,      archerDefense,   archerHealth,
                       archerAttackRange, archerMoveRange, archerSpeed,
                       archerPrize};

  statMap["Mage"] = {wizardAttack,      wizardDefense,   wizardHealth,
                     wizardAttackRange, wizardMoveRange, wizardSpeed,
                     wizardPrize};

  statMap["Knight"] = {knightAttack,      knightDefense,   knightHealth,
                       knightAttackRange, knightMoveRange, knightSpeed,
                       knightPrize};

  statMap["Monster"] = {monsterAttack,      monsterDefense,   monsterHealth,
                        monsterAttackRange, monsterMoveRange, monsterSpeed,
                        monsterPrize};

  commanderMap["Thassa"] = {thassaAttack,      thassaDefense,   thassaHealth,
                            thassaAttackRange, thassaMoveRange, thassaSpeed,
                            thassaPrize};

  commanderSwitch["Thassa"] = CommanderType::THASSA;

  commanderMap["Zamdran"] = {
      zamdranAttack,    zamdranDefense, zamdranHealth, zamdranAttackRange,
      zamdranMoveRange, zamdranSpeed,   zamdranPrize};

  commanderSwitch["Zamdran"] = CommanderType::ZAMRAN;
}

UnitFactory::~UnitFactory() = default;

Unit* UnitFactory::newBattalion(const std::string type, Team* team, Box* box,
                                int size) {
  if (statMap.find(type) == statMap.end()) return nullptr;
  const auto textureName =
      (team->getColor() == Color::BLUE ? "Units-Blue" : "Units-Red") + type;
  auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                            statMap[type], type, size);
  team->addUnit(unit);

  return unit;
}

Commander* UnitFactory::newCommander(const std::string type, Team* team,
                                     Box* box) {
  Commander* commander = nullptr;
  auto textureName = "Units-" + type;
  switch (commanderSwitch[type]) {
    case CommanderType::THASSA:
      commander = new Thassa(scene_, TextureManager::get(textureName), box,
                             commanderMap[type]);
      break;
    case CommanderType::ZAMRAN:
      commander = new Zamdran(scene_, TextureManager::get(textureName), box,
                              commanderMap[type]);
      break;
    default:
      return nullptr;
  }

  team->addUnit(commander);
  return commander;
}

const UnitStats UnitFactory::getStats(std::string type) {
  return statMap[type];
}

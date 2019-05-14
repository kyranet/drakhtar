// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "UnitFactory.h"

#include "GameObjects/Battalion.h"
#include "GameObjects/Commanders/Sheissah.h"
#include "GameObjects/Commanders/Thassa.h"
#include "GameObjects/Commanders/Zamdran.h"
#include "GameObjects/Commanders/Valar.h"
#include "GameObjects/Commanders/RedValar.h"
#include "GameObjects/Commanders/Dreilay.h"
#include "GameObjects/Commanders/Abeizhul.h"
#include "GameObjects/Unit.h"
#include "Managers/TextureManager.h"
#include "Scenes/Scene.h"
#include "Team.h"
#include "Utils/Constants.h"

UnitFactory::UnitFactory(Scene* scene) : scene_(scene) {
  statMap["Soldier"] = SOLDIER_STATS;

  statMap["Archer"] = ARCHER_STATS;

  statMap["Mage"] = MAGE_STATS;

  statMap["Knight"] = KNIGHT_STATS;

  statMap["Monster"] = MONSTER_STATS;

  commanderMap["Thassa"] = THASSA_STATS;

  commanderSwitch["Thassa"] = CommanderType::THASSA;

  commanderMap["Zamdran"] = ZAMDRAN_STATS;

  commanderSwitch["Zamdran"] = CommanderType::ZAMDRAN;

  commanderMap["Sheissah"] = SHEISSAH_STATS;

  commanderSwitch["Sheissah"] = CommanderType::SHEISSAH;

  commanderMap["BlueValar"] = VALAR_STATS;

  commanderSwitch["BlueValar"] = CommanderType::VALAR;

  commanderMap["RedValar"] = VALAR_STATS;

  commanderSwitch["RedValar"] = CommanderType::REDVALAR;

  commanderMap["Dreilay"] = DREILAY_STATS;

  commanderSwitch["Dreilay"] = CommanderType::DREILAY;

  commanderMap["Abeizhul"] = ABEIZHUL_STATS;

  commanderSwitch["Abeizhul"] = CommanderType::ABEIZHUL;
}

UnitFactory::~UnitFactory() = default;

Unit* UnitFactory::newBattalion(const std::string& type, Team* team, Box* box,
                                byte size) {
  if (statMap.find(type) == statMap.end()) return nullptr;
  const auto textureName =
      (team->getColor() == Color::BLUE ? "Units-Blue" : "Units-Red") + type;
  auto unit = new Battalion(scene_, TextureManager::get(textureName), box,
                            statMap[type], type, size);
  team->addUnit(unit);

  return unit;
}

Commander* UnitFactory::newCommander(const std::string& type, Team* team,
                                     Box* box) {
  Commander* commander = nullptr;
  auto textureName = "Units-" + type;
  switch (commanderSwitch[type]) {
    case CommanderType::THASSA:
      commander = new Thassa(scene_, TextureManager::get(textureName), box,
                             commanderMap[type]);
      break;
    case CommanderType::ZAMDRAN:
      commander = new Zamdran(scene_, TextureManager::get(textureName), box,
                              commanderMap[type]);
      break;
    case CommanderType::SHEISSAH:
      commander = new Sheissah(scene_, TextureManager::get(textureName), box,
                               commanderMap[type]);
      break;
    case CommanderType::VALAR:
      commander = new Valar(scene_, TextureManager::get(textureName), box,
                             commanderMap[type]);
      break;
    case CommanderType::REDVALAR:
      commander = new RedValar(scene_, TextureManager::get(textureName), box,
                            commanderMap[type]);
      break;
    case CommanderType::DREILAY:
      commander = new Dreilay(scene_, TextureManager::get(textureName), box,
                            commanderMap[type]);
      break;
    case CommanderType::ABEIZHUL:
      commander = new Abeizhul(scene_, TextureManager::get(textureName), box,
                            commanderMap[type]);
      break;
    default:
      return nullptr;
  }

  team->addUnit(commander);
  return commander;
}

const UnitStats UnitFactory::getStats(const std::string& type) {
  return statMap[type];
}

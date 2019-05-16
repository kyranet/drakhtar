// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <map>
#include <string>

class Scene;
class Team;
class Box;
class Unit;
class Commander;
struct UnitStats;

enum class CommanderType { THASSA, ZAMDRAN, SHEISSAH, VALAR, REDVALAR, DREILAY, ABEIZHUL };

class UnitFactory {
  Scene* scene_;
  std::map<std::string, UnitStats> statMap;
  std::map<std::string, UnitStats> commanderMap;
  std::map<std::string, CommanderType> commanderSwitch;

 public:
  explicit UnitFactory(Scene* scene);
  ~UnitFactory();
  Unit* newBattalion(const std::string& type, Team* team, Box* box, uint16_t size);
  Commander* newCommander(const std::string& type, Team* team, Box* box);

  const UnitStats getStats(const std::string& type);
};

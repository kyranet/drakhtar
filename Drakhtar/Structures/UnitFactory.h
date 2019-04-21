// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include <map>
#include <string>
#pragma once

class Scene;
class Team;
class Box;
class Unit;
class Commander;
struct UnitStats;

enum CommanderType { THASSA, ZAMRAN };

class UnitFactory {
  Scene* scene_;
  std::map<std::string, UnitStats> statMap;
  std::map<std::string, UnitStats> commanderMap;
  std::map<std::string, CommanderType> commanderSwitch;

 public:
  explicit UnitFactory(Scene* scene);
  ~UnitFactory();
  Unit* newBattalion(const std::string type, Team* team, Box* box, int size);
  Commander* newCommander(const std::string type, Team* team, Box* box);

  const UnitStats getStats(std::string type);
};

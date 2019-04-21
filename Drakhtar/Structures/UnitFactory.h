// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include <map>

#pragma once

class Scene;
class Team;
class Box;
class Unit;
class Thassa;
class Zamdran;
struct UnitStats;

class UnitFactory {
  Scene *scene_;
  std::map<std::string, UnitStats> statMap;

 public:
  explicit UnitFactory(Scene *scene);
  ~UnitFactory();
  Unit *newSoldier(Team *team, Box *box, int size) const;
  Unit *newArcher(Team *team, Box *box, int size) const;
  Unit *newKnight(Team *team, Box *box, int size) const;
  Unit *newWizard(Team *team, Box *box, int size) const;
  Unit *newMonster(Team *team, Box *box, int size) const;

  Thassa *newThassa(Team *team, Box *box) const;
  Zamdran *newZamdran(Team *team, Box *box) const;

  UnitStats getStats(std::string type);
};

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <vector>

class Scene;
class Team;
class Box;
class Unit;

class UnitFactory {
 private:
  Scene *scene_;

 public:
  explicit UnitFactory(Scene *scene);
  ~UnitFactory();
  Unit *newSoldier(Team *team, Box *box, int size);
  Unit *newArcher(Team *team, Box *box, int size);
  Unit *newKnight(Team *team, Box *box, int size);
  Unit *newWizard(Team *team, Box *box, int size);
  Unit *newMonster(Team *team, Box *box, int size);
};

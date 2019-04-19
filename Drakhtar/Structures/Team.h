// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <vector>

class Unit;
class Commander;
class Board;
class UnitsController;

enum class Color { BLUE, RED };

class Team final {
  std::vector<Unit*> units_{};
  std::vector<Commander*> commanders_{};
  Color color_;
  UnitsController* controller_ = nullptr;

 public:
  explicit Team(Color color);
  ~Team();

  void addCommander(Commander* commander);
  void removeCommander(Commander* commander);
  std::vector<Commander*> getCommanders() const;

  void addUnit(Unit* unit);
  void removeUnit(Unit* unit);
  std::vector<Unit*> getUnits() const;
  void sortUnits();

  void setController(UnitsController* controller);
  UnitsController* getController() const;

  Color getColor() const;
};

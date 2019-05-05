// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <array>
#include <vector>

class Scene;
class Unit;

class TurnManager final {
  std::vector<Unit*> units_;
  size_t position_;

 public:
  TurnManager(std::vector<Unit*> team1, std::vector<Unit*> team2);
  ~TurnManager();
  void next();
  void remove(Unit* unit);

  Unit* getTurnFor() const;
  void sortUnits();
  Unit* getActiveUnit();

  template<size_t N>
  std::array<Unit*, N> getNextUnits() const {
    std::array<Unit*, N> units;

    auto it = units_.begin() + position_;
    for (size_t i = 0, max = units.size(); i < max; i++) {
      units[i] = *it;
      if (++it == units_.end()) it = units_.begin();
    }

    return units;
  }
};

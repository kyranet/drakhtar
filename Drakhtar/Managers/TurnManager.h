// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <array>
#include <vector>

class Scene;
class Unit;

class TurnManager final {
  struct Turn {
    std::vector<Unit*> units;
    size_t position;
  };
  Turn allUnits_;
  size_t turn_ = 0;

  std::array<Unit*, 8> calculated_{};

 public:
  TurnManager(Scene* scene, std::vector<Unit*> team1, std::vector<Unit*> team2);
  ~TurnManager();
  void next();
  void prepare();
  void remove(Unit* unit);
  Unit* getTurnFor() const;
  std::array<Unit*, 8> getCalculated() { return calculated_; }
  void sortTurn();
};

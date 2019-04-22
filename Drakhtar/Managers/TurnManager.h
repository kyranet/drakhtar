// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <array>
#include <vector>

#include "SDL.h"

class Scene;
class Unit;

class TurnManager final {
  struct Turn {
    std::vector<Unit*> units;
    size_t position;
  };
  std::array<Turn, 2> teams_;
  size_t turn_ = 0;

  std::array<Unit*, 8> calculated_{};

 public:
  TurnManager(Scene* scene, std::vector<Unit*> team1, std::vector<Unit*> team2);
  ~TurnManager();
  void next();
  void prepare();

  void remove(Unit* unit);
  Unit* getTurnFor() const;

  std::array<Turn, 2> getTeams() { return teams_; }
  void setTeam(Turn team, int pos) { teams_[pos] = team; }
  std::array<Unit*, 8> getCalculated() { return calculated_; }
};

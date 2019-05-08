// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Structures/Team.h"
#include <array>
#include <vector>
#include "Utils/Vector2D.h"

class Unit;
class Team;

class State {
  struct UnitState {
    Unit* unit_;
    Color team_;
    Vector2D<int> position_;
    int attack;
    int health;
    int minimumAttack;
    int defense;
    int maxHealth;
    int attackRange;
    int moveRange;
    int speed;
    int prize;
  };

  bool hasMoved_ = false;
  bool hasAttacked_ = false;
  bool hasUsedSkills_ = false;

  int rows_ = 0, columns_ = 0;
  std::vector<UnitState> turns_{};
  std::vector<UnitState> board_{};

  void insert(const std::vector<Unit*>& units);
 public:
  State();
  void setUnits(const std::vector<Unit*>&, const std::vector<Unit*>&);
  void setBoard(int rows, int columns);

  void next();

  void setAt(Vector2D<int> position, const State::UnitState& state);
  State::UnitState getAt(Vector2D<int> position) const;
  void move(Vector2D<int> from, Vector2D<int> to);
  void removeAt(Vector2D<int> position);

  void remove(Vector2D<int> position);

  Unit* getActiveUnit() const;

  template<size_t N>
  std::array<Unit*, N> getNextUnits() const {
    std::array<Unit*, N> units;

    auto it = turns_.begin();
    for (size_t i = 0, max = units.size(); i < max; i++) {
      units[i] = *it;
      if (++it == turns_.end()) it = turns_.begin();
    }

    return units;
  }

};



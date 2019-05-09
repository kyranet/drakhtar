// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <array>
#include <vector>
#include "Structures/Team.h"
#include "Utils/Vector2D.h"

class Unit;
class Team;

class State {
  struct UnitState {
    UnitState()
        : unit_(nullptr),
          team_(Color::BLUE),
          position_({0, 0}),
          attack_(0),
          health_(0),
          minimumAttack_(0),
          defense_(0),
          maxHealth_(0),
          attackRange_(0),
          moveRange_(0),
          speed_(0),
          prize_(0),
          counterAttacked_(false) {}
    UnitState(Unit* unit, Color team, Vector2D<int> position, int attack,
              int health, int minimumAttack, int defense, int maxHealth,
              int attackRange, int moveRange, int speed, int prize,
              bool counterAttacked)
        : unit_(unit),
          team_(team),
          position_(position),
          attack_(attack),
          health_(health),
          minimumAttack_(minimumAttack),
          defense_(defense),
          maxHealth_(maxHealth),
          attackRange_(attackRange),
          moveRange_(moveRange),
          speed_(speed),
          prize_(prize),
          counterAttacked_(counterAttacked) {}
    Unit* unit_;
    Color team_;
    Vector2D<int> position_;
    int attack_;
    int health_;
    int minimumAttack_;
    int defense_;
    int maxHealth_;
    int attackRange_;
    int moveRange_;
    int speed_;
    int prize_;
    bool counterAttacked_;
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
  bool move(const Vector2D<int>& from, const Vector2D<int>& to);
  bool attack(const Vector2D<int>& from, const Vector2D<int>& to);
  void removeAt(Vector2D<int> position);

  void remove(Vector2D<int> position);

  Unit* getActiveUnit() const;

  template <size_t N>
  std::array<Unit*, N> getNextUnits() const {
    std::array<Unit*, N> units;

    auto it = turns_.begin();
    for (size_t i = 0, max = units.size(); i < max; i++) {
      units[i] = *it;
      if (++it == turns_.end()) it = turns_.begin();
    }

    return units;
  }

  /**
   * \brief Checks if two cells are within a certain range of each other.
   * \param from: The box from which distances will be calculated.
   * \param to: The box we are checking to be in range.
   * \param range: The number of boxes we can reach in any direction.
   * \return Whether or not the two boxes are "range" or less boxes away
   */
  bool isInRange(const Vector2D<int>& from, const Vector2D<int>& to,
                 int range) const;

  /**
   * \brief Checks if two cells are within a certain range of each other,
   * considering path-finding.
   * \param from: The box from which distances will be calculated.
   * \param to: The box we are checking to be in range.
   * \param range: The number of boxes we can reach in any direction.
   * \return Whether or not the two boxes are "range" or less boxes away,
   * considering path-finding.
   */
  bool isInMoveRange(const Vector2D<int>& from, const Vector2D<int>& to,
                     int range) const;

  std::vector<Vector2D<int>> getCellsInMovementRange(const Vector2D<int>& from,
                                                     int range) const;
  std::vector<Vector2D<int>> getCellsInAttackRange(const Vector2D<int>& from,
                                                   Color color,
                                                   int range) const;
  std::vector<Vector2D<int>> findPath(const Vector2D<int>& start,
                                      const Vector2D<int>& end) const;
};

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
          position_({0U, 0U}),
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
    UnitState(Unit* unit, Color team, Vector2D<byte> position, int attack,
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
    Vector2D<byte> position_;
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

  byte rows_ = 0, columns_ = 0;
  std::vector<UnitState> turns_{};
  std::vector<UnitState> board_{};

  void insert(const std::vector<Unit*>& units);

 public:
  State();
  void setUnits(const std::vector<Unit*>&, const std::vector<Unit*>&);
  void setBoard(byte rows, byte columns);

  void next();

  void setAt(Vector2D<byte> position, const State::UnitState& state);
  State::UnitState getAt(Vector2D<byte> position) const;
  bool move(const Vector2D<byte>& from, const Vector2D<byte>& to);
  bool attack(const Vector2D<byte>& from, const Vector2D<byte>& to);
  void removeAt(Vector2D<byte> position);

  void remove(Vector2D<byte> position);

  Unit* getActiveUnit() const;

  template <size_t N>
  std::array<Unit*, N> getNextUnits() const {
    std::array<Unit*, N> units;

    auto it = turns_.begin();
    for (byte i = 0, max = units.size(); i < max; i++) {
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
  bool isInRange(const Vector2D<byte>& from, const Vector2D<byte>& to,
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
  bool isInMoveRange(const Vector2D<byte>& from, const Vector2D<byte>& to,
                     int range) const;

  std::vector<Vector2D<byte>> getCellsInMovementRange(
      const Vector2D<byte>& from, int range) const;
  std::vector<Vector2D<byte>> getCellsInAttackRange(
      const Vector2D<byte>& from, Color color, int range) const;
  std::vector<Vector2D<byte>> findPath(const Vector2D<byte>& start,
                                         const Vector2D<byte>& end) const;
};

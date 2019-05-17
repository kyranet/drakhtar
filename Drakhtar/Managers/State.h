// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <array>
#include <functional>
#include <map>
#include <stack>
#include <utility>
#include <vector>
#include "Structures/Team.h"
#include "Utils/Vector2D.h"

class Unit;
class Team;
class UnitsController;

struct Modifier;

struct UnitState {
  UnitState()
      : unit_(nullptr),
        team_(Color::BLUE),
        position_({0U, 0U}),
        attack_(0U),
        health_(0U),
        minimumAttack_(0U),
        defense_(0U),
        maxHealth_(0U),
        attackRange_(0U),
        moveRange_(0U),
        speed_(0U),
        prize_(0U),
        battalionSize_(0U),
        counterAttacked_(false),
        counterAttackable_(true) {}
  UnitState(Unit* unit, Color team, Vector2D<uint16_t> position,
            uint16_t attack, uint16_t health, uint16_t minimumAttack,
            uint16_t defense, uint16_t maxHealth, uint16_t attackRange,
            uint16_t moveRange, uint16_t speed, uint16_t prize,
            uint16_t battalionSize, bool counterAttacked,
            bool counterAttackable, std::vector<Modifier> modifiers)
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
        battalionSize_(battalionSize),
        counterAttacked_(counterAttacked),
        counterAttackable_(counterAttackable),
        modifiers_(std::move(modifiers)) {}
  Unit* unit_;
  Color team_;
  Vector2D<uint16_t> position_;
  uint16_t attack_;
  uint16_t health_;
  uint16_t minimumAttack_;
  uint16_t defense_;
  uint16_t maxHealth_;
  uint16_t attackRange_;
  uint16_t moveRange_;
  uint16_t speed_;
  uint16_t prize_;
  uint16_t battalionSize_;
  bool counterAttacked_;
  bool counterAttackable_;
  std::vector<Modifier> modifiers_;
};

class State;

struct Modifier {
  Unit* caster_;
  std::function<UnitState(const UnitState&)> run_;
  int16_t duration_;
};

struct SkillState {
  Unit* caster_;
  int16_t cooldown_;
};

class State {
  uint16_t rows_ = 0, columns_ = 0;
  std::vector<UnitState> turns_{};
  std::vector<UnitState> board_{};
  std::map<std::string, SkillState> skillsUsed_{};
  UnitsController* controller_ = nullptr;

  void insert(const std::vector<Unit*>& units);

  static std::stack<State> stack_;

 public:
  State();
  void setUnits(const std::vector<Unit*>&, const std::vector<Unit*>&);
  void setBoard(uint16_t rows, uint16_t columns);

  void save();
  void restore();

  std::vector<UnitState> getBoard() const;

  void setController(UnitsController* controller);
  UnitsController* getController() const;

  void next();

  int16_t getRemainingSkillCooldown(const std::string& skillId);
  void castSkill(Unit* caster, const std::string& skillId, int16_t cooldown);

  void setAt(const Vector2D<uint16_t>& position, const UnitState& state);
  const UnitState getAt(const Vector2D<uint16_t>& position) const;
  const UnitState getModifiedAt(const Vector2D<uint16_t>& position) const;
  void addModifierAt(const Vector2D<uint16_t>& position,
                     const Modifier& modifier);

  Unit* getUnitAt(const Vector2D<uint16_t>& position) const;

  bool move(const Vector2D<uint16_t>& from, const Vector2D<uint16_t>& to);
  bool attack(const Vector2D<uint16_t>& from, const Vector2D<uint16_t>& to,
              bool counterAttack = false);
  bool attack(const Vector2D<uint16_t>& to, uint16_t damage);
  void removeAt(const Vector2D<uint16_t>& position);

  Unit* getActiveUnit() const;

  template <size_t N>
  std::array<Unit*, N> getNextUnits() const {
    std::array<Unit*, N> units;

    auto it = turns_.begin();
    for (uint16_t i = 0, max = units.size(); i < max; i++) {
      units[i] = (*it).unit_;
      if (++it == turns_.end()) it = turns_.begin();
    }

    return units;
  }

  int getDistance(const Vector2D<uint16_t>& from,
                  const Vector2D<uint16_t>& to) const;

  /**
   * \brief Checks if two cells are within a certain range of each other.
   * \param from: The box from which distances will be calculated.
   * \param to: The box we are checking to be in range.
   * \param range: The number of boxes we can reach in any direction.
   * \return Whether or not the two boxes are "range" or less boxes away
   */
  bool isInRange(const Vector2D<uint16_t>& from, const Vector2D<uint16_t>& to,
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
  bool isInMoveRange(const Vector2D<uint16_t>& from,
                     const Vector2D<uint16_t>& to, int range) const;

  std::vector<Vector2D<uint16_t>> getCellsInMovementRange(
      const Vector2D<uint16_t>& from, int range) const;
  std::vector<Vector2D<uint16_t>> getCellsInAttackRange(
      const Vector2D<uint16_t>& from, Color color, int range) const;
  std::vector<Vector2D<uint16_t>> findPath(const Vector2D<uint16_t>& start,
                                           const Vector2D<uint16_t>& end) const;
};

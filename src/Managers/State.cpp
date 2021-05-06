// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "State.h"

#include <third_party/AStar.h>

#include <algorithm>

#include "Controllers/UnitsController.h"
#include "GameObjects/Battalion.h"
#include "GameObjects/Box.h"
#include "GameObjects/Commanders/Commander.h"
#include "GameObjects/Skill.h"
#include "GameObjects/Unit.h"
#include "Tracker.h"
#include "TrackerEvents/AttackEvent.h"
#include "TrackerEvents/BuyUnitsEvent.h"

std::stack<State> State::stack_;  //  NOLINT

State::State() = default;

std::vector<UnitState> State::getBoard() const { return board_; }

void State::setController(UnitsController* controller) {
  controller_ = controller;
}

void State::save() { stack_.push(*this); }
void State::restore() {
  if (stack_.empty()) return;
  const auto old = stack_.top();
  rows_ = old.rows_;
  columns_ = old.columns_;
  turns_ = old.turns_;
  board_ = old.board_;
  skillsUsed_ = old.skillsUsed_;
  controller_ = old.controller_;
  stack_.pop();
}

UnitsController* State::getController() const { return controller_; }

void State::next() {
  const auto it = turns_.begin();
  const auto unit = *it;
  turns_.erase(it);
  turns_.push_back(unit);
  controller_ = nullptr;

  // If it's a commander,
  if (getActiveUnit()->isCommander()) {
    // Update all skills across the board
    for (auto& stats : board_) {
      if (stats.modifiers_.empty()) continue;
      size_t i = 0;
      while (i < stats.modifiers_.size()) {
        if (stats.modifiers_[i].duration_ != -1 &&
            (stats.modifiers_[i].caster_ == getActiveUnit()) &&
            (--stats.modifiers_[i].duration_ <= 0)) {
          stats.modifiers_.erase(stats.modifiers_.begin() +
                                 static_cast<int64_t>(i));
        } else {
          ++i;
        }
      }
    }

    // Update all skills
    for (auto& pair : skillsUsed_) {
      if (pair.second.caster_ != getActiveUnit()) continue;
      if (pair.second.cooldown_ > 0) {
        --pair.second.cooldown_;
      }
    }
  }

  // Clone the state but with the counterAttacked value set to false
  const auto previous = getAt(getActiveUnit()->getBox()->getIndex());

  UnitState updated(previous.unit_, previous.team_, previous.position_,
                    previous.attack_, previous.health_, previous.minimumAttack_,
                    previous.defense_, previous.maxHealth_,
                    previous.attackRange_, previous.moveRange_, previous.speed_,
                    previous.prize_, previous.battalionSize_, false,
                    previous.counterAttackable_, previous.modifiers_);
  setAt(updated.position_, updated);
}

int16_t State::getRemainingSkillCooldown(const std::string& skillId) {
  if (skillsUsed_.count(skillId) == 0) return 0;
  return skillsUsed_[skillId].cooldown_;
}

void State::castSkill(Unit* caster, const std::string& skillId,
                      int16_t cooldown) {
  skillsUsed_[skillId] = {caster, cooldown};
}

Unit* State::getActiveUnit() const { return turns_.front().unit_; }

void State::setUnits(const std::vector<Unit*>& first,
                     const std::vector<Unit*>& second) {
  turns_.reserve(first.size() + second.size());
  insert(first);
  insert(second);

  std::sort(turns_.begin(), turns_.end(),
            [](const UnitState& a, const UnitState& b) {
              return a.speed_ > b.speed_;
            });
}

void State::setBoard(const uint16_t rows, const uint16_t columns) {
  board_.clear();
  rows_ = rows;
  columns_ = columns;
  board_.resize(rows_ * columns_);

  for (uint16_t x = 0U; x < columns; ++x) {
    for (uint16_t y = 0U; y < rows; ++y) {
      removeAt({x, y});
    }
  }
}

void State::insert(const std::vector<Unit*>& units) {
  for (const auto& unit : units) {
    const auto base = unit->getBaseStats();
    const auto color = unit->getTeam()->getColor();
    const auto boxPosition = unit->getBox()->getIndex();

    // If it's a commander, calculate it wisely.
    if (unit->isCommander()) {
      UnitState state(unit, color, boxPosition, base.attack, base.maxHealth, 1,
                      base.defense, base.maxHealth, base.attackRange,
                      base.moveRange, base.speed, base.prize, 0, false, true,
                      {});
      turns_.push_back(state);
      setAt(boxPosition, state);
    } else {
      const auto battalion = reinterpret_cast<Battalion*>(unit);
      const auto size = battalion->getBattalionSize();
      UnitState state(
          unit, color, boxPosition, static_cast<uint16_t>(base.attack * size),
          static_cast<uint16_t>(base.maxHealth * size), size, base.defense,
          static_cast<uint16_t>(base.maxHealth * size), base.attackRange,
          base.moveRange, base.speed, static_cast<uint16_t>(base.prize * size),
          size, false, true, {});
      turns_.push_back(state);
      setAt(boxPosition, state);
    }
  }
}

void State::setAt(const Vector2D<uint16_t>& position, const UnitState& state) {
  board_[position.getX() * rows_ + position.getY()] = state;
}

void State::addModifierAt(const Vector2D<uint16_t>& position,
                          const Modifier& modifier) {
  auto& stats = board_[position.getX() * rows_ + position.getY()];
  stats.modifiers_.push_back(modifier);
}

const UnitState State::getAt(const Vector2D<uint16_t>& position) const {
  return board_[position.getX() * rows_ + position.getY()];
}

const UnitState State::getModifiedAt(const Vector2D<uint16_t>& position) const {
  auto stats = board_[position.getX() * rows_ + position.getY()];
  const auto modifiers = stats.modifiers_;
  for (const auto& modifier : modifiers) stats = modifier.run_(stats);
  return stats;
}

Unit* State::getUnitAt(const Vector2D<uint16_t>& position) const {
  return board_[position.getX() * rows_ + position.getY()].unit_;
}

bool State::move(const Vector2D<uint16_t>& from, const Vector2D<uint16_t>& to) {
  const auto previous = getAt(from);
  if (previous.unit_ == nullptr) return false;

  removeAt(from);

  UnitState state(previous.unit_, previous.team_, to, previous.attack_,
                  previous.health_, previous.minimumAttack_, previous.defense_,
                  previous.maxHealth_, previous.attackRange_,
                  previous.moveRange_, previous.speed_, previous.prize_,
                  previous.battalionSize_, previous.counterAttacked_,
                  previous.counterAttackable_, previous.modifiers_);

  setAt(to, state);
  return true;
}

bool State::attack(const Vector2D<uint16_t>& from, const Vector2D<uint16_t>& to,
                   const bool counterAttack) {
  const auto previous = getAt(from);
  if (previous.unit_ == nullptr) return false;

  const auto enemy = getAt(to);
  if (enemy.unit_ == nullptr) return false;

  const auto modifiedPrevious = getModifiedAt(from);
  const auto modifiedEnemy = getModifiedAt(to);

  const auto damage = std::min(
      std::max(static_cast<int>(modifiedPrevious.attack_ *
                                (1.0 - modifiedEnemy.defense_ / 100.0)),
               static_cast<int>(modifiedPrevious.minimumAttack_)),
      static_cast<int>(modifiedEnemy.maxHealth_));
  const auto health = static_cast<uint16_t>(
      damage > modifiedEnemy.health_ ? 0 : modifiedEnemy.health_ - damage);

  // Tracker::getInstance().trackEvent(new AttackEvent(
  //    modifiedPrevious.unit_->getType(), modifiedEnemy.unit_->getType(),
  //    damage));

  if (health == 0) {
    removeAt(to);
    if (controller_) controller_->onKill(enemy);

    // Remove from the turn vector
    for (auto it = turns_.begin(); it != turns_.end(); ++it) {
      if ((*it).unit_ == enemy.unit_) {
        turns_.erase(it);
        break;
      }
    }
  } else {
    auto counterAttacked = enemy.counterAttacked_;
    if (modifiedPrevious.counterAttackable_ && !counterAttack &&
        !(enemy.unit_->getType() == "Archer" &&
          isInRange(enemy.position_, previous.position_, 1)) &&
        isInRange(enemy.position_, previous.position_,
                  modifiedEnemy.attackRange_) &&
        !counterAttacked) {
      counterAttacked = true;
      attack(to, from, true);
    }

    if (enemy.battalionSize_ != 0) {
      // Update battalion size
      const auto battalionSize = static_cast<uint16_t>(
          std::ceil(static_cast<float>(health * enemy.battalionSize_) /
                    static_cast<float>(enemy.maxHealth_)));
      const auto attack = static_cast<uint16_t>(
          enemy.unit_->getBaseStats().attack * battalionSize);
      const auto minimumDamage = static_cast<uint16_t>(battalionSize);

      const UnitState updated(
          enemy.unit_, enemy.team_, enemy.position_, attack, health,
          minimumDamage, enemy.defense_, enemy.maxHealth_, enemy.attackRange_,
          enemy.moveRange_, enemy.speed_, enemy.prize_, battalionSize,
          counterAttacked, enemy.counterAttackable_, enemy.modifiers_);
      setAt(to, updated);
      if (controller_) controller_->onDamage(updated);
    } else {
      // Update commander size
      const UnitState updated(
          enemy.unit_, enemy.team_, enemy.position_, enemy.attack_, health,
          enemy.minimumAttack_, enemy.defense_, enemy.maxHealth_,
          enemy.attackRange_, enemy.moveRange_, enemy.speed_, enemy.prize_, 0,
          counterAttacked, enemy.counterAttackable_, enemy.modifiers_);
      setAt(to, updated);
      if (controller_) controller_->onDamage(updated);
    }
  }

  return true;
}

bool State::attack(const Vector2D<uint16_t>& to, uint16_t damage) {
  const auto enemy = getAt(to);
  if (enemy.unit_ == nullptr) return false;

  const auto modifiedEnemy = getModifiedAt(to);

  const auto health = static_cast<uint16_t>(
      damage >= modifiedEnemy.health_ ? 0 : modifiedEnemy.health_ - damage);

  // Tracker::getInstance().trackEvent(
  //    new AttackEvent("Unknown",
  //                    modifiedEnemy.unit_->getType(), damage));

  if (health == 0) {
    removeAt(to);
    if (controller_) controller_->onKill(enemy);

    // Remove from the turn vector
    for (auto it = turns_.begin(); it != turns_.end(); ++it) {
      if ((*it).unit_ == enemy.unit_) {
        turns_.erase(it);
        break;
      }
    }
  } else {
    if (enemy.battalionSize_ != 0) {
      // Update battalion size
      const auto battalionSize = static_cast<uint16_t>(
          std::ceil(static_cast<float>(health * enemy.battalionSize_) /
                    static_cast<float>(modifiedEnemy.maxHealth_)));
      const auto attack = static_cast<uint16_t>(
          enemy.unit_->getBaseStats().attack * battalionSize);
      const auto minimumDamage = static_cast<uint16_t>(battalionSize);

      const UnitState updated(
          enemy.unit_, enemy.team_, enemy.position_, attack, health,
          minimumDamage, enemy.defense_, enemy.maxHealth_, enemy.attackRange_,
          enemy.moveRange_, enemy.speed_, enemy.prize_, battalionSize,
          enemy.counterAttacked_, enemy.counterAttackable_, enemy.modifiers_);
      setAt(to, updated);
      if (controller_) controller_->onDamage(updated);
    } else {
      // Update commander size
      const UnitState updated(
          enemy.unit_, enemy.team_, enemy.position_, enemy.attack_, health,
          enemy.minimumAttack_, enemy.defense_, enemy.maxHealth_,
          enemy.attackRange_, enemy.moveRange_, enemy.speed_, enemy.prize_, 0,
          enemy.counterAttacked_, enemy.counterAttackable_, enemy.modifiers_);
      setAt(to, updated);
      if (controller_) controller_->onDamage(updated);
    }
  }

  return true;
}

void State::removeAt(const Vector2D<uint16_t>& position) {
  setAt(position, {nullptr,
                   Color::BLUE,
                   position,
                   0,
                   0,
                   0,
                   0,
                   0,
                   0,
                   0,
                   0,
                   0,
                   0,
                   false,
                   false,
                   {}});
}

std::vector<Vector2D<uint16_t>> State::findPath(
    const Vector2D<uint16_t>& start, const Vector2D<uint16_t>& end) const {
  // Create path generator
  AStar::Generator generator;
  generator.setWorldSize({columns_, rows_});
  generator.setHeuristic(AStar::Heuristic::euclidean);
  generator.setDiagonalMovement(false);

  // Load board obstacles
  for (const auto& cell : board_) {
    if (cell.unit_ != nullptr)
      generator.addCollision({cell.position_.getX(), cell.position_.getY()});
  }

  // Remove itself as an obstacle
  generator.removeCollision({start.getX(), start.getY()});

  // Find path
  auto path = generator.findPath({start.getX(), start.getY()},
                                 {end.getX(), end.getY()});
  // If it is only the first cell, return empty.
  if (path.size() <= 1) return {};

  std::vector<Vector2D<uint16_t>> pathList;
  for (const auto& coordinate : path) {
    pathList.insert(pathList.begin(), {static_cast<uint16_t>(coordinate.x),
                                       static_cast<uint16_t>(coordinate.y)});
  }

  return pathList;
}

int State::getDistance(const Vector2D<uint16_t>& from,
                       const Vector2D<uint16_t>& to) const {
  const auto distanceX = abs(static_cast<int>(to.getX() - from.getX()));
  const auto distanceY = abs(static_cast<int>(to.getY() - from.getY()));
  return distanceX + distanceY;
}

bool State::isInRange(const Vector2D<uint16_t>& from,
                      const Vector2D<uint16_t>& to, int range) const {
  return range >= getDistance(from, to);
}

bool State::isInMoveRange(const Vector2D<uint16_t>& from,
                          const Vector2D<uint16_t>& to, int range) const {
  // Absolute range will always be equal or larger than movement range
  if (!isInRange(from, to, range)) return false;

  auto path = findPath(from, to);
  if (path.empty()) {
    return false;
  }
  return range >= static_cast<int>(path.size() - 1);
}

std::vector<Vector2D<uint16_t>> State::getCellsInMovementRange(
    const Vector2D<uint16_t>& from, int range) const {
  std::vector<Vector2D<uint16_t>> cells;
  for (const auto& cell : board_) {
    if (isInMoveRange(from, cell.position_, range))
      cells.push_back(cell.position_);
  }
  return cells;
}

std::vector<Vector2D<uint16_t>> State::getCellsInAttackRange(
    const Vector2D<uint16_t>& from, Color color, int range) const {
  std::vector<Vector2D<uint16_t>> cells;
  for (const auto& cell : board_) {
    if (cell.unit_ != nullptr && cell.team_ != color &&
        isInRange(from, cell.position_, range))
      cells.push_back(cell.position_);
  }
  return cells;
}

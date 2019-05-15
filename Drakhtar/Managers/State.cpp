// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "State.h"
#include <third_party/AStar.h>
#include <algorithm>
#include "Controllers/UnitsController.h"
#include "GameObjects/Battalion.h"
#include "GameObjects/Box.h"
#include "GameObjects/Commanders/Commander.h"
#include "GameObjects/Unit.h"

State::State() = default;

void State::setController(UnitsController* controller) {
  controller_ = controller;
}

void State::next() {
  const auto it = turns_.begin();
  const auto unit = *it;
  turns_.erase(it);
  turns_.push_back(unit);
  controller_ = nullptr;
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

void State::setBoard(const byte rows, const byte columns) {
  board_.clear();
  rows_ = rows;
  columns_ = columns;
  board_.resize(rows_ * columns_);

  for (byte x = 0U; x < columns; ++x) {
    for (byte y = 0U; y < rows; ++y) {
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
                      base.moveRange, base.speed, base.prize, false);
      turns_.push_back(state);
      setAt(boxPosition, state);
    } else {
      const auto battalion = reinterpret_cast<Battalion*>(unit);
      const auto size = battalion->getBattalionSize();
      UnitState state(unit, color, boxPosition,
                      static_cast<byte>(base.attack * size),
                      static_cast<byte>(base.maxHealth * size), size,
                      base.defense, static_cast<byte>(base.maxHealth * size),
                      base.attackRange, base.moveRange, base.speed,
                      static_cast<byte>(base.prize * size), false);
      turns_.push_back(state);
      setAt(boxPosition, state);
    }
  }
}

void State::setAt(const Vector2D<byte>& position, const UnitState& state) {
  board_[position.getX() * rows_ + position.getY()] = state;
}

const UnitState State::getAt(const Vector2D<byte>& position) const {
  return board_[position.getX() * rows_ + position.getY()];
}

Unit* State::getUnitAt(const Vector2D<byte>& position) const {
  return board_[position.getX() * rows_ + position.getY()].unit_;
}

bool State::move(const Vector2D<byte>& from, const Vector2D<byte>& to) {
  const auto previous = getAt(from);
  if (previous.unit_ == nullptr) return false;

  removeAt(from);

  UnitState state(previous.unit_, previous.team_, to, previous.attack_,
                  previous.health_, previous.minimumAttack_, previous.defense_,
                  previous.maxHealth_, previous.attackRange_,
                  previous.moveRange_, previous.speed_, previous.prize_,
                  previous.counterAttacked_);

  setAt(to, state);
  return true;
}

bool State::attack(const Vector2D<byte>& from, const Vector2D<byte>& to,
                   const bool counterAttack) {
  const auto previous = getAt(from);
  if (previous.unit_ == nullptr) return false;

  const auto enemy = getAt(to);
  if (enemy.unit_ == nullptr) return false;

  const auto damage = std::min(
      std::max(
          static_cast<int>(previous.attack_ * (1.0 - enemy.defense_ / 100.0)),
          static_cast<int>(previous.minimumAttack_)),
      static_cast<int>(enemy.maxHealth_));
  const auto health = std::max(enemy.health_ - damage, 0);

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
    if (!(enemy.unit_->getType() == "Archer" &&
          isInRange(enemy.position_, previous.position_, 1)) &&
        isInRange(enemy.position_, previous.position_, enemy.attackRange_) &&
        !counterAttacked) {
      counterAttacked = true;
      if (!counterAttack) attack(to, from, true);
    }

    const auto minimumAttack = enemy.minimumAttack_;
    // TODO(kyranet): Add Battalion's logic

    UnitState updated(enemy.unit_, enemy.team_, enemy.position_, enemy.attack_,
                      static_cast<byte>(health), minimumAttack, enemy.defense_,
                      enemy.maxHealth_, enemy.attackRange_, enemy.moveRange_,
                      enemy.speed_, enemy.prize_, counterAttacked);

    setAt(to, updated);
    if (controller_) controller_->onDamage(updated);
  }

  return true;
}

void State::removeAt(const Vector2D<byte>& position) {
  setAt(position,
        {nullptr, Color::BLUE, position, 0, 0, 0, 0, 0, 0, 0, 0, 0, false});
}

std::vector<Vector2D<byte>> State::findPath(const Vector2D<byte>& start,
                                            const Vector2D<byte>& end) const {
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

  std::vector<Vector2D<byte>> pathList;
  for (const auto& coordinate : path) {
    pathList.insert(pathList.begin(), {static_cast<byte>(coordinate.x),
                                       static_cast<byte>(coordinate.y)});
  }

  return pathList;
}

bool State::isInRange(const Vector2D<byte>& from, const Vector2D<byte>& to,
                      int range) const {
  const auto distanceX = abs(static_cast<int>(to.getX() - from.getX()));
  const auto distanceY = abs(static_cast<int>(to.getY() - from.getY()));
  const auto totalDistance = distanceX + distanceY;

  return range >= totalDistance;
}

bool State::isInMoveRange(const Vector2D<byte>& from, const Vector2D<byte>& to,
                          int range) const {
  auto path = findPath(from, to);
  if (path.empty()) {
    return false;
  }
  return range >= static_cast<const int>(path.size() - 1);
}

std::vector<Vector2D<byte>> State::getCellsInMovementRange(
    const Vector2D<byte>& from, int range) const {
  std::vector<Vector2D<byte>> cells;
  for (const auto& cell : board_) {
    if (isInMoveRange(from, cell.position_, range))
      cells.push_back(cell.position_);
  }
  return cells;
}

std::vector<Vector2D<byte>> State::getCellsInAttackRange(
    const Vector2D<byte>& from, Color color, int range) const {
  std::vector<Vector2D<byte>> cells;
  for (const auto& cell : board_) {
    if (cell.unit_ != nullptr && cell.team_ != color &&
        isInRange(from, cell.position_, range))
      cells.push_back(cell.position_);
  }
  return cells;
}

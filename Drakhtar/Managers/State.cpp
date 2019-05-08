#include "State.h"
#include <algorithm>
#include "GameObjects/Battalion.h"
#include "GameObjects/Commanders/Commander.h"
#include "GameObjects/Unit.h"

State::State() = default;

void State::next() {
  const auto it = turns_.begin();
  const auto unit = *it;
  turns_.erase(it);
  turns_.push_back(unit);

  hasMoved_ = false;
  hasAttacked_ = false;
  hasUsedSkills_ = false;
}

void State::remove(Vector2D<int> position) {}

Unit* State::getActiveUnit() const { return turns_.front().unit_; }

void State::setUnits(const std::vector<Unit*>& first,
                     const std::vector<Unit*>& second) {
  turns_.reserve(first.size() + second.size());
  insert(first);
  insert(second);

  std::sort(turns_.begin(), turns_.end(),
            [](UnitState a, UnitState b) { return a.speed > b.speed; });
}

void State::setBoard(int rows, int columns) {
  board_.reserve(rows * columns);
  rows_ = rows;
  columns_ = columns;

  for (int x = 0; x < columns; ++x) {
    for (int y = 0; y < rows; ++y) {
      board_[x * rows + y] = { nullptr, Color::BLUE, { x, y }, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    }
  }
}

void State::insert(const std::vector<Unit*>& units) {
  for (const auto& unit : units) {
    const auto base = unit->getBaseStats();
    const auto color = unit->getTeam()->getColor();
    const auto boxPosition = unit->getBoxPosition();

    // If it's a commander, calculate it wisely.
    if (unit->isCommander()) {
      State::UnitState state {unit, color, boxPosition, base.attack, base.maxHealth,
                        1, base.defense, base.maxHealth, base.attackRange,
                        base.moveRange, base.speed, base.prize};
      turns_.push_back(state);
      setAt(boxPosition, state);
    } else {
      const auto battalion = reinterpret_cast<Battalion*>(unit);
      const auto size = battalion->getBattalionSize();
      State::UnitState state{unit, color, boxPosition, base.attack * size,
                             base.maxHealth * size, size, base.defense,
                             base.maxHealth * size, base.attackRange, base.moveRange,
                             base.speed, base.prize * size};
      turns_.push_back(state);
      setAt(boxPosition, state);
    }
  }
}

void State::setAt(Vector2D<int> position, const State::UnitState& state) {
  board_[position.getX() * rows_ + position.getY()] = state;
}

State::UnitState State::getAt(Vector2D<int> position) const {
  return board_[position.getX() * rows_ + position.getY()];
}

void State::move(Vector2D<int> from, Vector2D<int> to) {
  const auto previous = getAt(from);
  if (previous.unit_ == nullptr) return;

  removeAt(from);
  setAt(to, previous);
}

void State::removeAt(Vector2D<int> position) {
  setAt(position, { nullptr, Color::BLUE, position, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
}

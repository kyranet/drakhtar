// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TurnManager.h"

#include <algorithm>
#include <utility>

#include "GameObjects/Unit.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"
#include "TextureManager.h"
#include "Utils/Constants.h"

TurnManager::TurnManager(std::vector<Unit*> team1, std::vector<Unit*> team2)
    : position_(0) {
  units_.reserve(team1.size() + team2.size());  // preallocate memory
  units_.insert(units_.end(), team1.begin(), team1.end());
  units_.insert(units_.end(), team2.begin(), team2.end());

  sortUnits();
}

TurnManager::~TurnManager() = default;

void TurnManager::next() {
  if (++position_ >= units_.size()) position_ = 0;
}

void TurnManager::remove(Unit* unit) {
  size_t x = 0;
  for (auto it = units_.begin(); it != units_.end(); ++it, ++x) {
    if (*it != unit) continue;
    units_.erase(it);
    // If the unit's turn was behind the cursor, we want the cursor to go back.
    // So when I have:
    // 1 2 3 4 5
    //     ^
    // And I remove the second, the cursor must decrease:
    // 1 3 4 5
    //   ^
    if (x < position_) --position_;

    // Stop the loop
    break;
  }
}

Unit* TurnManager::getTurnFor() const { return units_[position_]; }

void TurnManager::sortUnits() {
  std::sort(units_.begin(), units_.end(), [](Unit* a, Unit* b) {
    return a->getStats().speed > b->getStats().speed;
  });
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TurnManager.h"

#include <utility>
#include <algorithm>

#include "GameObjects/Unit.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"
#include "TextureManager.h"
#include "Utils/Constants.h"

TurnManager::TurnManager(std::vector<Unit*> team1,
                         std::vector<Unit*> team2) {
  std::vector<Unit*> allVector;
  allVector.reserve(team1.size() + team2.size());  // preallocate memory
  allVector.insert(allVector.end(), team1.begin(), team1.end());
  allVector.insert(allVector.end(), team2.begin(), team2.end());
  allUnits_ = {std::move(allVector), 0};

  sortTurn();
  prepare();
}

TurnManager::~TurnManager() = default;

void TurnManager::prepare() {
  auto aIt = allUnits_.units.begin() + allUnits_.position;
  size_t i = 0;
  while (true) {
    calculated_[i] = *aIt;
    if (++i == calculated_.size()) break;
    if (++aIt == allUnits_.units.end()) aIt = allUnits_.units.begin();
  }
}

void TurnManager::next() {
  if (++allUnits_.position >= allUnits_.units.size()) allUnits_.position = 0;
  prepare();
}

void TurnManager::remove(Unit* unit) {
  auto turn = &allUnits_;

  size_t x = 0;
  for (auto it = turn->units.begin(); it != turn->units.end(); ++it, ++x) {
    if (*it != unit) continue;
    turn->units.erase(it);
    // If the unit's turn was behind the cursor, we want the cursor to go back.
    // So when I have:
    // 1 2 3 4 5
    //     ^
    // And I remove the second, the cursor must decrease:
    // 1 3 4 5
    //   ^
    if (x < turn->position) --turn->position;

    // Stop the loop
    break;
  }

  prepare();
}

Unit* TurnManager::getTurnFor() const {
  const auto turn = allUnits_;
  return turn.units.size() > turn.position ? turn.units[turn.position]
                                           : nullptr;
}

void TurnManager::sortTurn() {
  std::sort(allUnits_.units.begin(), allUnits_.units.end(),
            [](Unit* a, Unit* b) {
              return a->getBaseStats().speed > b->getBaseStats().speed;
            });
}

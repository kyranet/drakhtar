// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TurnManager.h"

#include <utility>

#include "GameObjects/Unit.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"
#include "TextureManager.h"
#include "Utils/Constants.h"

TurnManager::TurnManager(Scene* scene, std::vector<Unit*> team1,
                         std::vector<Unit*> team2) {
  teams_[0] = {std::move(team1), 0};
  teams_[1] = {std::move(team2), 0};

  prepare();
}

TurnManager::~TurnManager() = default;

void TurnManager::prepare() {
  const auto blueTeam = teams_[0];
  const auto redTeam = teams_[1];

  const auto blueUnits = blueTeam.units;
  const auto redUnits = redTeam.units;

  // Clear up all calculated values
  for (auto& i : calculated_) {
    i = nullptr;
  }

  if (blueUnits.empty()) {
    if (redUnits.empty()) return;
    size_t x = 0;
    for (auto& i : calculated_) {
      i = redUnits[x];
      if (++x == blueUnits.size()) x = 0;
    }
  } else if (redUnits.empty()) {
    if (blueUnits.empty()) return;
    size_t x = 0;
    for (auto& i : calculated_) {
      i = blueUnits[x];
      if (++x == redUnits.size()) x = 0;
    }
  } else {
    auto a = turn_ == 0 ? blueUnits : redUnits;
    auto b = turn_ == 0 ? redUnits : blueUnits;

    auto aIt = a.begin() + (turn_ == 0 ? blueTeam.position : redTeam.position);
    auto bIt = b.begin() + (turn_ == 0 ? redTeam.position : blueTeam.position);
    size_t i = 0;
    while (true) {
      calculated_[i] = *aIt;
      if (++i == calculated_.size()) break;
      if (++aIt == a.end()) aIt = a.begin();

      calculated_[i] = *bIt;
      if (++i == calculated_.size()) break;
      if (++bIt == b.end()) bIt = b.begin();
    }
  }
}

void TurnManager::next() {
  if (++teams_[turn_].position >= teams_[turn_].units.size())
    teams_[turn_].position = 0;
  if (++turn_ == teams_.size()) turn_ = 0;
  prepare();
}

void TurnManager::remove(Unit* unit) {
  const auto team = unit->getTeam();
  auto turn = &teams_[team->getColor() == Color::BLUE ? 0 : 1];

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
  const auto turn = teams_[turn_];
  return turn.units.size() > turn.position ? turn.units[turn.position]
                                           : nullptr;
}

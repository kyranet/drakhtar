// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TurnBar.h"
#include <utility>
#include "Managers/TextureManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"
#include "Unit.h"
#include "Utils/Constants.h"

TurnBar::TurnBar(Scene* scene, std::vector<Unit*> team1,
                 std::vector<Unit*> team2)
    : GameObject(
          scene, TextureManager::get("UI-turnBar"),
          Vector2D<int>(static_cast<int>(WIN_WIDTH - WIN_WIDTH / 5.3),
                        WIN_HEIGHT - WIN_HEIGHT / 13),
          Vector2D<int>(WIN_WIDTH / 2, static_cast<int>(WIN_WIDTH / 16.44))) {
  teams_[0] = {std::move(team1), 0};
  teams_[1] = {std::move(team2), 0};
  addChild(new GameObject(scene_, TextureManager::get("UI-circle"),
                          {static_cast<int>(WIN_WIDTH - WIN_WIDTH / 2.05),
                           WIN_HEIGHT - WIN_HEIGHT / 13},
                          {WIN_WIDTH / 7, WIN_WIDTH / 7}));

  prepare();
}

TurnBar::~TurnBar() = default;

void TurnBar::prepare() {
  const auto scene = reinterpret_cast<GameScene*>(getScene());
  const auto blue = scene->getTeam1();
  const auto red = scene->getTeam2();
  if (!blue || !red) return;

  const auto blueUnits = blue->getUnits();
  const auto redUnits = red->getUnits();

  if (blueUnits.empty()) {
    if (redUnits.empty()) return;
    size_t x = 0;
    for (auto& i : calculated_) {
      i = blueUnits[x];
      if (++x == blueUnits.size()) x = 0;
    }
  } else if (redUnits.empty()) {
    if (blueUnits.empty()) return;
    size_t x = 0;
    for (auto& i : calculated_) {
      i = redUnits[x];
      if (++x == redUnits.size()) x = 0;
    }
  } else {
    auto a = turn_ == 0 ? blueUnits : redUnits;
    auto b = turn_ == 0 ? redUnits : blueUnits;

    auto aIt = a.begin();
    auto bIt = b.begin();
    for (auto& i : calculated_) {
      i = *aIt;
      if (++aIt == a.end()) aIt = a.begin();
      i = *bIt;
      if (++bIt == b.end()) bIt = b.begin();
    }
  }
}

void TurnBar::next() {
  if (++turn_ == teams_.size()) turn_ = 0;
  prepare();
}

void TurnBar::render() const {
  GameObject::render();

  size_t i = 0;
  calculated_[i]->render({static_cast<int>(WIN_WIDTH - WIN_WIDTH / 1.92 +
                                           1.0 * WIN_HEIGHT / 18.18),
                          static_cast<int>(WIN_HEIGHT - WIN_HEIGHT / 12.5),
                          WIN_HEIGHT / 5, WIN_HEIGHT / 5});
  ++i;
  for (const auto max = calculated_.size(); i < max; ++i) {
    calculated_[i]->render({static_cast<int>(WIN_WIDTH - WIN_WIDTH / 1.9 +
                                             (i + 1.0) * WIN_HEIGHT / 11.0),
                            static_cast<int>(WIN_HEIGHT - WIN_HEIGHT / 12.5),
                            WIN_HEIGHT / 8, WIN_HEIGHT / 8});
  }
}

void TurnBar::remove(Unit* unit) {
  const auto team = unit->getTeam();
  auto turn = teams_[team->getColor() == Color::BLUE ? 0 : 1];

  size_t x = 0;
  for (auto it = turn.units.begin(); it != turn.units.end(); ++it, ++x) {
    if (*it != unit) continue;
    turn.units.erase(it);
    // If the unit's turn was behind the cursor, we want the cursor to go back.
    // So when I have:
    // 1 2 3 4 5
    //     ^
    // And I remove the second, the cursor must decrease:
    // 1 3 4 5
    //   ^
    if (x < turn.position) --turn.position;

    // Stop the loop
    break;
  }
}
Unit* TurnBar::getTurnFor() const {
  const auto turn = teams_[turn_];
  return turn.units[turn.position];
}

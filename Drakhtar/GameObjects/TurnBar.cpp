// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TurnBar.h"
#include <Scenes/GameScene.h>
#include "Managers/TextureManager.h"
#include "Scenes/Scene.h"
#include "Structures/Team.h"
#include "Unit.h"
#include "Utils/Constants.h"

TurnBar::TurnBar(Scene* scene)
    : GameObject(
          scene, TextureManager::get("UI-turnBar"),
          Vector2D<int>(static_cast<int>(WIN_WIDTH - WIN_WIDTH / 5.3),
                        WIN_HEIGHT - WIN_HEIGHT / 13),
          Vector2D<int>(WIN_WIDTH / 2, static_cast<int>(WIN_WIDTH / 16.44))) {
  calculated_.resize(8);
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

  calculated_.clear();
  if (blueUnits.empty()) {
    if (redUnits.empty()) return;
    for (size_t i = 0, x = 0, m = calculated_.capacity(); i < m; i++) {
      calculated_.push_back(blueUnits[x]);
      if (++x == blueUnits.size()) x = 0;
    }
  } else if (redUnits.empty()) {
    if (blueUnits.empty()) return;
    for (size_t i = 0, x = 0, m = calculated_.capacity(); i < m; i++) {
      calculated_.push_back(redUnits[x]);
      if (++x == redUnits.size()) x = 0;
    }
  } else {
    auto a = turn_ == 0 ? blueUnits : redUnits;
    auto b = turn_ == 0 ? redUnits : blueUnits;

    auto aIt = blueUnits.begin();
    auto bIt = redUnits.begin();
    for (size_t i = 0, m = calculated_.capacity(); i < m; i++) {
      calculated_.push_back(*aIt);
      if (++aIt == a.end()) aIt = a.begin();
      calculated_.push_back(*bIt);
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
  for (const auto max = calculated_.capacity(); i < max; ++i) {
    calculated_[i]->render({static_cast<int>(WIN_WIDTH - WIN_WIDTH / 1.9 +
                                             (i + 1.0) * WIN_HEIGHT / 11.0),
                            static_cast<int>(WIN_HEIGHT - WIN_HEIGHT / 12.5),
                            WIN_HEIGHT / 8, WIN_HEIGHT / 8});
  }
}

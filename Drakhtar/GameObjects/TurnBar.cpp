// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TurnBar.h"
#include <utility>
#include "Managers/TextureManager.h"
#include "Managers/TurnManager.h"
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
  turnManager_ = new TurnManager(std::move(team1), std::move(team2));

  const auto circle =
      new GameObject(scene_, TextureManager::get("UI-circle"),
                     {static_cast<int>(WIN_WIDTH - WIN_WIDTH / 2.05),
                      WIN_HEIGHT - WIN_HEIGHT / 13},
                     {WIN_WIDTH / 7, WIN_WIDTH / 7});
  circle->setTransparent(true);
  addChild(circle);
}

TurnBar::~TurnBar() { delete turnManager_; }

void TurnBar::render() const {
  std::array<Unit*, 8> calculated = turnManager_->getNextUnits<8>();

  // Do nothing if there are no calculated units.
  if (calculated.front() == nullptr) return;
  GameObject::render();

  size_t i = 0;
  Vector2D<int> position(0, 0);
  Vector2D<int> size(0, 0);

  position.set(
      static_cast<int>(WIN_WIDTH - WIN_WIDTH / 1.92 + 1.0 * WIN_HEIGHT / 18.18),
      static_cast<int>(WIN_HEIGHT - WIN_HEIGHT / 12.5));
  size.set(WIN_HEIGHT / 5, WIN_HEIGHT / 5);
  calculated[i]->render({position.getX() - size.getX() / 2,
                         position.getY() - size.getY() / 2, size.getX(),
                         size.getY()});
  ++i;
  for (const auto max = calculated.size(); i < max; ++i) {
    if (calculated[i] == nullptr) continue;
    position.set(
        static_cast<int>(WIN_WIDTH - WIN_WIDTH / 2 + (i + 1) * WIN_HEIGHT / 11),
        static_cast<int>(WIN_HEIGHT - WIN_HEIGHT / 12.5));
    size.set(WIN_HEIGHT / 8, WIN_HEIGHT / 8);
    calculated[i]->render({position.getX() - size.getX() / 2,
                           position.getY() - size.getY() / 2, size.getX(),
                           size.getY()});
  }
}

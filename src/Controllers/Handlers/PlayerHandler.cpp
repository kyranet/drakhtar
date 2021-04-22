// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "PlayerHandler.h"
#include "Controllers/PlayerController.h"
#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
#include "GameObjects/Unit.h"
#include "Managers/Input.h"

PlayerHandler::PlayerHandler(PlayerController* controller)
    : EventListener(nullptr), controller_(controller) {}

void PlayerHandler::run(const SDL_Event) {
  if (controller_->getLocked() || !Input::isMouseButtonUp(MouseKey::LEFT))
    return;

  const auto gameObject = Input::screenMouseToRay();
  if (!gameObject) return;

  const auto box = dynamic_cast<Box*>(gameObject);
  if (!box) return;

  if (!controller_->hasMoved() && box->isEmpty()) {
    controller_->onClickMove(box);
  } else if (!controller_->hasAttacked()) {
    controller_->onClickAttack(box);
  }
}

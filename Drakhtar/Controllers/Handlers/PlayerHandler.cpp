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
  if (controller_->getLocked() || !Input::isMouseButtonDown(MouseKey::LEFT))
    return;

  const auto gameObject = Input::screenMouseToRay();
  if (!gameObject) return;

  // Ignore Unit's "hitboxes" and assume it's a click to the board, so get the
  // box at the mouse's coordinates
  const auto unit = dynamic_cast<Unit*>(gameObject);
  const auto box = unit ? controller_->getBoard()->getBoxAtCoordinates(
                              Input::getMousePosition())
                        : dynamic_cast<Box*>(gameObject);
  if (!box) return;

  if (!controller_->hasMoved() && box->isEmpty()) {
    controller_->onClickMove(box);
  } else if (!controller_->hasAttacked()) {
    controller_->onClickAttack(box);
  }
}

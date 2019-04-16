// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "ListenerOnHover.h"
#include "Managers/Input.h"

void ListenerOnHover::run(const SDL_Event event) {
  const auto hovered = Input::screenMouseToRay() == getGameObject();
  if (hovered) {
    if (hovered_) {
      onHoverStay();
    } else {
      hovered_ = true;
      onHoverStart();
    }
  } else if (hovered_) {
    hovered_ = false;
    onHoverStop();
  }
}

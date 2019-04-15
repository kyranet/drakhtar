// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "ListenerOnClick.h"
#include "Managers/Input.h"

void ListenerOnClick::run(const SDL_Event event) {
  GameObject* asd;
  GameObject* asd2;
  switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
      if (Input::screenMouseToRay() != getGameObject()) return;
      if (!clicked_) onClickStart();
      clicked_ = true;
      break;
    case SDL_MOUSEBUTTONUP:
      asd = getGameObject();
      asd2 = Input::screenMouseToRay();
      if (Input::screenMouseToRay() != getGameObject()) return;
      std::cout << "asd";
      if (clicked_) onClickStop();
      clicked_ = false;
      break;
    default:
      if (clicked_) onClickStay();
      break;
  }
}

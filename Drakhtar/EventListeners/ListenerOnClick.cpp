// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "ListenerOnClick.h"
#include "Managers/SDLAudioManager.h"
void ListenerOnClick::run(const SDL_Event event) {
  auto area = getGameObject()->getRect();

  SDL_Point p = {event.motion.x, event.motion.y};

  switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
      SDLAudioManager::getInstance()->playChannel(0, 1, 0);
      if (!SDL_PointInRect(&p, &area)) return;
      if (!clicked_) onClickStart(p);
      clicked_ = true;
      break;
    case SDL_MOUSEBUTTONUP:
      if (!SDL_PointInRect(&p, &area)) return;
      if (clicked_) onClickStop(p);
      clicked_ = false;
      break;
    default:
      if (clicked_) onClickStay(p);
      break;
  }
}

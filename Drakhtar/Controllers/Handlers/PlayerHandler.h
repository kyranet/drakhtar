// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "EventListeners/EventListener.h"

class PlayerController;

class PlayerHandler : public EventListener {
 private:
  PlayerController* controller_;

 public:
  explicit PlayerHandler(PlayerController* controller);
  void run(SDL_Event event) override;
};

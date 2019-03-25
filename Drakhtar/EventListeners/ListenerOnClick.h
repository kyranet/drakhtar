// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../GameObjects/GameObject.h"
#include "EventListener.h"
#include "SDL.h"

class ListenerOnClick : public EventListener {
 private:
  bool clicked_ = false;

 public:
  ListenerOnClick(GameObject *gameObject) : EventListener(gameObject) {}
  virtual void run(SDL_Event event);
  virtual void onClickStart(SDL_Point point) {}
  virtual void onClickStay(SDL_Point point) {}
  virtual void onClickStop(SDL_Point point) {}
};

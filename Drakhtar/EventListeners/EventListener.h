// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../GameObjects/GameObject.h"

class EventListener {
 private:
  GameObject *gameObject_;

 public:
  EventListener(GameObject *gameObject);
  virtual ~EventListener();
  virtual void run(SDL_Event event) = 0;
  GameObject *getGameObject() const;
};

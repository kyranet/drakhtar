// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../GameObjects/GameObject.h"

class EventListener {
  GameObject *gameObject_;

 public:
  explicit EventListener(GameObject *gameObject);
  virtual ~EventListener() = default;
  virtual void run(SDL_Event event) = 0;
  GameObject *getGameObject() const;
};

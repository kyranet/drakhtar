// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Button.h"
#include "GameObject.h"

class Pause : public GameObject {
 private:
  Button* restart;
  Button* resume;
  Button* exit;

 public:
  explicit Pause(Scene* scene);
  void handleEvents(SDL_Event e) override;
};

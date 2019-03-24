// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <functional>
#include "GameObject.h"
#include "SDL.h"

using Callback = void();

class Button : public GameObject {
 protected:
  Callback *callback_;

 public:
  Button(Scene *scene, Texture *texture, Vector2D<int> pos, Vector2D<int> size,
         Callback *callback);
  void handleEvents(SDL_Event e);
};

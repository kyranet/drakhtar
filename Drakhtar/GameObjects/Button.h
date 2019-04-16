// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <functional>

#include "GameObject.h"
#include "SDL.h"

class Button final : public GameObject {
 private:
  std::function<void()> callback_;

 public:
  Button(Scene* scene, Texture* texture, const Vector2D<int>& pos,
         const Vector2D<int>& size, std::function<void()> callback);
  void update() override;
  void handleEvents(SDL_Event e) override;
};

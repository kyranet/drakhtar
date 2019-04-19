// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <functional>
#include "GameObject.h"
#include "SDL.h"
#include "../GameObjects/ButtonText.h"

class Button final : public GameObject {
 private:
  std::function<void()> callback_;
  std::string buttonText_;

 public:
  Button(Scene* scene, Texture* texture, const Vector2D<int>& pos,
         const Vector2D<int>& size, std::function<void()> callback,
         const std::string& text, const std::string& fontFile);
  void update() override;
};

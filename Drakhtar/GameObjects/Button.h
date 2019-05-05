// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <functional>

#include "../GameObjects/ButtonText.h"
#include "GameObject.h"
#include "SDL.h"

class Button final : public GameObject {
 private:
  std::function<void()> callback_;

 protected:
  bool hovered_ = false;
  int increSize_;

 public:
  Button(Scene* scene, Texture* texture, const Vector2D<int>& pos,
         const Vector2D<int>& size, std::function<void()> callback,
         const std::string& text, const std::string& fontFile);
  void call();
  void render() const override;
  void update() override;
  void setColor(const SDL_Color& color);
  SDL_Rect getRect() const override;
  SDL_Rect changeRect() const;
};

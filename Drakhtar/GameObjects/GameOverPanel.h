// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"

class Button;
class Text;

class GameOverPanel : public GameObject {
 public:
  GameOverPanel(Scene* scene, Texture* texture, const Vector2D<int>& position,
                const Vector2D<int>& size, bool victory);
  ~GameOverPanel() = default;
};
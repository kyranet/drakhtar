// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObjects/GameObject.h"

class Sequence : public GameObject {
 public:
  Sequence(Scene *scene, Texture *texture);
  Sequence(Scene *scene, Texture *texture, const Vector2D<int> &position,
           const Vector2D<int> &size);

  virtual void next() = 0;
  virtual void skip() = 0;
};

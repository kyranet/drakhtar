// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <array>
#include <vector>
#include "GameObject.h"
#include "SDL.h"

class Scene;
class Unit;

class TurnBar final : public GameObject {
  struct Turn {
    std::vector<Unit*> units;
    size_t position;
  };
  std::array<Turn, 2> teams_;
  size_t turn_ = 0;

  std::vector<Unit*> calculated_;

 public:
  TurnBar(Scene* scene);
  ~TurnBar();
  void next();
  void prepare();
  void render() const override;
};

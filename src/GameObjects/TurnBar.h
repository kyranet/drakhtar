// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"

class Scene;
class Unit;

class TurnBar final : public GameObject {
 public:
  TurnBar(Scene* scene, const std::vector<Unit*>& team1,
          const std::vector<Unit*>& team2);
  ~TurnBar();

  void render() const override;
};

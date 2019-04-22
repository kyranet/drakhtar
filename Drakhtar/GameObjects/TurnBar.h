// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"

class Scene;
class Unit;
class TurnManager;

class TurnBar final : public GameObject {
  TurnManager* turnManager_;

 public:
  TurnBar(Scene* scene, std::vector<Unit*> team1, std::vector<Unit*> team2);
  ~TurnBar();

  void render() const override;

  TurnManager* getTurnManager() const { return turnManager_; }
};

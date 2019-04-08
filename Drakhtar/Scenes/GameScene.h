// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"

class Team;

class GameScene final : public Scene {
  Team* team1_ = nullptr;
  Team* team2_ = nullptr;
  int battle_;

 public:
  explicit GameScene(int battle);
  virtual ~GameScene();
  void preload() override;
  void pause() override;
};

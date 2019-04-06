// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../GameObjects/Commanders/Thassa.h"
#include "../GameObjects/Commanders/Zamdran.h"
#include "Scene.h"

class Team;

class GameScene final : public Scene {
  Team* team1_ = nullptr;
  Team* team2_ = nullptr;
  Thassa* thassa_ = nullptr;
  Zamdran* zamdran_ = nullptr;

 public:
  virtual ~GameScene();
  void preload() override;
  void pause() override;
};

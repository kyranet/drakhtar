// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"

class Team;
class BoardController;

class GameScene final : public Scene {
  Team *team1_ = nullptr;
  Team *team2_ = nullptr;
  BoardController *boardController_;
  int battle_;

 public:
  explicit GameScene(int battle);
  virtual ~GameScene();
  void preload() override;
  void pause() override;
  void skipTurn() override;
};

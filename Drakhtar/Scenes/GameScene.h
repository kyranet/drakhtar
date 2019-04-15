// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"

class Team;
class Board;
class BoardController;
class UnitFactory;

class GameScene final : public Scene {
  Team *team1_ = nullptr;
  Team *team2_ = nullptr;
  Board *board_ = nullptr;
  BoardController *boardController_;
  int battle_;

 public:
  explicit GameScene(int battle);
  ~GameScene() override;
  void preload() override;
  void pause() override;
  void skipTurn() override;
  void loadRedTeam(UnitFactory &factory);
};

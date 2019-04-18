// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"

class Team;
class Board;
class UnitFactory;
class PlayerController;

class GameScene final : public Scene {
  Team* team1_ = nullptr;
  Team* team2_ = nullptr;
  Board* board_ = nullptr;
  PlayerController* playerController_;
  int battle_;

 public:
  explicit GameScene(int battle);
  ~GameScene() override;
  void preload() override;
  void pause() override;
  void loadRedTeam(UnitFactory& factory);

  Board* getBoard() const;
  Team* getTeam1() const;
  Team* getTeam2() const;
};

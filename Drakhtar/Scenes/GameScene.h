// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"

class Team;
class Board;
class UnitFactory;
class PlayerController;
class Unit;
class TutorialBox;

class GameScene final : public Scene {
  Team* team1_ = nullptr;
  Team* team2_ = nullptr;
  Board* board_ = nullptr;
  TutorialBox* tutorialBox = nullptr;
  int battle_;
  int prize_ = 0;
  int counter = 0;

 public:
  explicit GameScene(int battle);
  ~GameScene() override;
  void preload() override;
  void pause() override;
  void gameOver(bool victory);
  void addPrize(int prize);
  void saveStatus();
  void readLevel(UnitFactory& factory);

  Board* getBoard() const;
  int getBattleInd();

  void setTutorialBox();
  void tutorialCheckpoint(int counter);

  Team* getTeam1_() const { return team1_; }
  Team* getTeam2_() const { return team2_; }
  Team* getAlliedTeam(Unit* unit);
  Team* getEnemyTeam(Unit* unit);
};

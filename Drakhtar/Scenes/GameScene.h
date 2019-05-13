// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"

class Team;
class Board;
class UnitFactory;
class PlayerController;
class Unit;
class TutorialBox;
class State;

class GameScene final : public Scene {
  Team* team1_ = nullptr;
  Team* team2_ = nullptr;
  Board* board_ = nullptr;
  TutorialBox* tutorialBox = nullptr;
  State* state_ = nullptr;
  int battle_;
  int prize_ = 0;

 public:
  explicit GameScene(int battle);
  ~GameScene() override;
  void preload() override;
  void pause() override;
  void gameOver(bool victory);
  void addPrize(int prize);
  void saveStatus();
  void readLevel(UnitFactory& factory, std::vector<Unit*>& unitOrder);

  Board* getBoard() const;
  int getBattleInd();

  void activateTutorialBox() override;

  State* getState() const;

  Team* getAlliedTeam(Unit* unit);
  Team* getEnemyTeam(Unit* unit);
};

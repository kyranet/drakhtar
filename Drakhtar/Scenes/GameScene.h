// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"

class Team;

class GameScene : public Scene {
 private:
  Team* team1 = nullptr;
  Team* team2 = nullptr;

 public:
  virtual ~GameScene();
  void preload();
  void pause();
};

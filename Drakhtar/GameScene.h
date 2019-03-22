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

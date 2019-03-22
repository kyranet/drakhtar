#pragma once
#include "Scene.h"

class Team;
class GameObject;

class GameScene : public Scene {
 private:
  Team* team1 = nullptr;
  Team* team2 = nullptr;
  GameObject* pauseObject = nullptr;

 public:
  virtual ~GameScene();
  void resume();
  void preload();
  void pause();
};

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <stack>

using namespace std;
class Scene;

class SceneMachine {
 protected:
  stack<Scene *> sceneStack_;

 public:
  SceneMachine();
  virtual ~SceneMachine();
  void pushScene(Scene *state);
  void changeScene(Scene *state);
  void popScene();
  bool isEmpty() const;
  Scene *getCurrentScene();
};

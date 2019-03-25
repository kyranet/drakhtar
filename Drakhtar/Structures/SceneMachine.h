// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <stack>

class Scene;

class SceneMachine {
 protected:
  std::stack<Scene *> sceneStack_;

 public:
  SceneMachine();
  virtual ~SceneMachine();
  void pushScene(Scene *state);
  void changeScene(Scene *state);
  void popScene();
  bool isEmpty() const;
  Scene *getCurrentScene();
};

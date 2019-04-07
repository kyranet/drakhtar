// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <stack>

class Scene;

/**
 * \brief The Scene machine that manages all scenes.
 */
class SceneMachine final {
 protected:
  std::stack<Scene *> sceneStack_;

 public:
  SceneMachine();
  ~SceneMachine();
  SceneMachine(const SceneMachine &) = default;  // Copy Constructor
  SceneMachine(SceneMachine &&) = default;       // Move Constructor
  SceneMachine &operator=(const SceneMachine &) =
      default;                                         // Assignment Operator
  SceneMachine &operator=(SceneMachine &&) = default;  // Move Operator

  void pushScene(Scene *scene);
  void changeScene(Scene *scene);
  void popScene();
  bool isEmpty() const;
  Scene *getCurrentScene();
};

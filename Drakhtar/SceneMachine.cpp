// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "SceneMachine.h"
#include "Scene.h"

SceneMachine::SceneMachine() {}

SceneMachine::~SceneMachine() {
  while (!sceneStack_.empty()) {
    delete sceneStack_.top();
    sceneStack_.pop();
  }
}

void SceneMachine::pushScene(Scene *scene) { sceneStack_.push(scene); }

void SceneMachine::changeScene(Scene *scene) {
  popScene();
  pushScene(scene);
}

void SceneMachine::popScene() {
  if (!sceneStack_.empty()) {
    delete sceneStack_.top();
    sceneStack_.pop();
  }
}

bool SceneMachine::isEmpty() const {
    return sceneStack_.empty();
}

Scene *SceneMachine::getCurrentScene() {
  return sceneStack_.empty() ? nullptr : sceneStack_.top();
}

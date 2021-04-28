// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "SceneMachine.h"

#include "../Scenes/Scene.h"

SceneMachine::SceneMachine() = default;

SceneMachine::~SceneMachine() {
  while (!sceneStack_.empty()) {
    delete sceneStack_.top();
    sceneStack_.pop();
  }
}

void SceneMachine::pushScene(Scene* scene) { sceneStack_.push(scene); }

void SceneMachine::changeScene(Scene* scene) {
  if (!sceneStack_.empty()) {
    const auto previous = sceneStack_.top();
    previous->setOnEndHandler([this, scene, previous]() {
      sceneStack_.pop();
      if (scene) pushScene(scene);
      delete previous;
    });

    // False is passed to queue the scene to eventually finish
    previous->finish(false);
  } else if (scene) {
    pushScene(scene);
  }
}

void SceneMachine::popScene() { changeScene(nullptr); }

bool SceneMachine::isEmpty() const { return sceneStack_.empty(); }

Scene* SceneMachine::getCurrentScene() {
  return sceneStack_.empty() ? nullptr : sceneStack_.top();
}

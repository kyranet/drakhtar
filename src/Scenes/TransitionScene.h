// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"

class TransitionScene final : public Scene {
  size_t nLines[6] = {12, 8, 30, 5, 15, 10};

 public:
  explicit TransitionScene(int battle);
  void preload() override;
  // void run();
  int getBattleInd();

 private:
  int battle_;
  // DialogScene dialog;
};

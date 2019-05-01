// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <queue>
#include "TutorialSequence.h"

class TutorialLogic : public Sequence {
 public:
  void changeToNextTutorial(int counter);
};
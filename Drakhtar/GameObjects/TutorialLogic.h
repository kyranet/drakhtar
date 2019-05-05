// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <queue>
#include "TutorialSequence.h"

class TutorialLogic : public Sequence {
 public:
  static bool tutorialEnded(int counter, int tutorialLenght);

  static void changeToNextTutorial();
  static void updateCounter(int counter, int tutorialLenght);
  static bool firstTutorialEnded(int counter);
};
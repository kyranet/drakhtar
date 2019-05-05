// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TutorialLogic.h"

bool TutorialLogic::tutorialEnded(int counter, int tutorialLength) {
  if (counter == tutorialLength) return true;
}

void TutorialLogic::changeToNextTutorial() {}

void TutorialLogic::updateCounter(int counter, int tutorialLength) {
  if (counter <= tutorialLength)
    counter++;
  else
    counter = 0;
}

bool TutorialLogic::firstTutorialEnded(int counter) {
  if (counter == 2)
    return true;
  else
    return false;
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TutorialLogic.h"

bool TutorialLogic::tutorialEnded(int counter, int tutorialLenght) {
  if (counter == tutorialLenght) return true;
}

void TutorialLogic::changeToNextTutorial() {}

void TutorialLogic::updateCounter(int counter, int tutorialLenght) {
  if (counter <= tutorialLenght)
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

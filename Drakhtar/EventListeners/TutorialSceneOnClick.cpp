// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TutorialSceneOnClick.h"
#include "GameObjects/TutorialSequence.h"

void TutorialSceneOnClick::onClickStop() {
  static_cast<TutorialSequence *>(getGameObject()->getParent())  // NOLINT
      ->createNextTutorial();
}

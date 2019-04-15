// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TutorialSceneOnClick.h"
#include "GameObjects/TutorialSequence.h"

void TutorialSceneOnClick::onClickStop() {
  reinterpret_cast<TutorialSequence *>(getGameObject()->getParent())
      ->next();
}

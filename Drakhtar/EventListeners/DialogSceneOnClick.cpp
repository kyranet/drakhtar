// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "DialogSceneOnClick.h"
#include "GameObjects/DialogScene.h"

void DialogSceneOnClick::onClickStop() {
  static_cast<DialogScene*>(getGameObject()->getParent())->next();  // NOLINT
}

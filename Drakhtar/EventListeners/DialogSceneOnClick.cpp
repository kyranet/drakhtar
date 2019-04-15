// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "DialogSceneOnClick.h"
#include "GameObjects/DialogScene.h"

void DialogSceneOnClick::onClickStart() {
  reinterpret_cast<DialogScene *>(getGameObject()->getParent())->next();
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "DialogSceneOnClick.h"
#include "GameObjects/Base/Sequence.h"

void DialogSceneOnClick::onClickStop() {
  reinterpret_cast<Sequence *>(getGameObject()->getParent())->next();
}

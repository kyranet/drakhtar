// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "ButtonListener.h"
#include "GameObjects/Button.h"

void ButtonListener::onClickStop() {
  reinterpret_cast<Button*>(getGameObject())->call();
}

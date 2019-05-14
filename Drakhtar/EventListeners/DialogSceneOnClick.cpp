// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "DialogSceneOnClick.h"

#include "GameObjects/Base/Sequence.h"
#include "Managers/SDLAudioManager.h"
void DialogSceneOnClick::onClickStop() {
  reinterpret_cast<Sequence*>(getGameObject()->getParent())->next();
  SDLAudioManager::getInstance()->setChannelVolume(7, 2);
  SDLAudioManager::getInstance()->playChannel(13, 0, 2);
}

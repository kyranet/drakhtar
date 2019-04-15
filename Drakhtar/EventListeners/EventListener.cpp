// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "EventListener.h"

EventListener::EventListener(GameObject* gameObject)
    : gameObject_(gameObject) {}

GameObject* EventListener::getGameObject() const { return gameObject_; }

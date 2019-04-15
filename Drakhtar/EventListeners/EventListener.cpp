// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "EventListener.h"

EventListener::EventListener(GameObject* gameObject) : gameObject_(gameObject) {
  active_ = true;
}

GameObject* EventListener::getGameObject() const { return gameObject_; }

bool EventListener::getActive() { return active_; }

void EventListener::setActive(bool active) { active_ = active; }

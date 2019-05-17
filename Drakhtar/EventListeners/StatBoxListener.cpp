// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "StatBoxListener.h"

#include "GameObjects/Box.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/UnitDescriptionBox.h"
#include "Managers/Input.h"

StatBoxListener::StatBoxListener(Board* board, UnitDescriptionBox* statsPanel)
    : ListenerOnHover(reinterpret_cast<GameObject*>(board)),
      board_(board),
      statsPanel_(statsPanel) {}

StatBoxListener::~StatBoxListener() {}

void StatBoxListener::run(const SDL_Event) {
  const auto hovered = dynamic_cast<Box*>(Input::screenMouseToRay()) != nullptr;
  if (hovered) {
    if (hovered_) {
      onHoverStay();
    } else {
      hovered_ = true;
      onHoverStart();
    }
  } else if (hovered_) {
    hovered_ = false;
    onHoverStop();
  }
}

void StatBoxListener::onHoverStay() {
  const auto box = reinterpret_cast<Box*>(Input::screenMouseToRay());
  const auto unit = box->getContent();
  if (unit) {
    statsPanel_->setRenderable(true);
    statsPanel_->updateText(box->getContent());
  } else {
    statsPanel_->setRenderable(false);
  }
}

void StatBoxListener::onHoverStop() { statsPanel_->setRenderable(false); }

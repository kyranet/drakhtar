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
  const auto hovered = dynamic_cast<Box*>(Input::screenMouseToRay()) != NULL;
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
  Box* box = reinterpret_cast<Box*>(Input::screenMouseToRay());
  if (box->getContent() != nullptr) {
    statsPanel_->setRenderizable(true);
    statsPanel_->updateText(box->getContent());
  } else {
    statsPanel_->setRenderizable(false);
  }
}

void StatBoxListener::onHoverStop() { statsPanel_->setRenderizable(false); }

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Button.h"
#include <utility>
#include "Managers/Input.h"
#include "EventListeners/ButtonListener.h"

Button::Button(Scene* scene, Texture* texture, const Vector2D<int>& pos,
               const Vector2D<int>& size, std::function<void()> callback,
               const std::string& text, const std::string& fontFile)
    : GameObject(scene, texture, pos, size), callback_(std::move(callback)) {
  // Create the text
  const auto buttonText = new ButtonText(scene, text, fontFile, size, pos);
  buttonText->setTransparent(true);

  addChild(buttonText);
  addEventListener(new ButtonListener(this));
}

void Button::call() { callback_(); }

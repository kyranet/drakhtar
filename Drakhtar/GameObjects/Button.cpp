// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Button.h"
#include <utility>
#include "Managers/Input.h"
#include "Text.h"
#include "../Structures/Font.h"
#include "Managers/FontManager.h"

Button::Button(Scene* scene, Texture* texture, const Vector2D<int>& pos,
               const Vector2D<int>& size, std::function<void()> callback,
               const std::string& text, const std::string& fontFile)
    : GameObject(scene, texture, pos, size), callback_(std::move(callback)) {
  spriteText_ = text;

  const SDL_Color textColor = {0, 0, 0, 255};

  const auto buttonText_ = new Text(
      scene, FontManager::get(fontFile),
               Vector2D<int>(this->getRect().x + this->getRect().w / 10,
                             this->getRect().y + this->getRect().h / 200),
      textColor, spriteText_, this->getRect().w*0.95);

  buttonText_->setColor(textColor);
  buttonText_->setText(spriteText_, textColor, this->getRect().w * 0.75);
  buttonText_->setPosition(
      Vector2D<int>(this->getRect().x + buttonText_->getRect().w/ 50,
                    this->getRect().y - buttonText_->getRect().h/ 50));
  buttonText_->setSize({100, 70});
  //buttonText_->setSize(
  //    Vector2D<int>(this->getRect().x + buttonText_->getRect().w / 10,
    //                this->getRect().y - buttonText_->getRect().h / 10));

  addChild(buttonText_);
}

void Button::update() {
  GameObject::update();

  if ((Input::isMouseButtonDown(MouseKey::LEFT) ||
      Input::isMouseButtonDown(MouseKey::RIGHT)) &&
      reinterpret_cast<Button*>(Input::screenMouseToRay()) == this) {
    callback_();
  }
}

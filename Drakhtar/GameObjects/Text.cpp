// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Text.h"
#include "../Structures/Game.h"
#include "../Structures/Texture.h"

Text::Text(Scene* scene, Font* font, Vector2D<int> pos, SDL_Color color,
           std::string text, int lineJumpLimit)
    : GameObject(scene, new Texture(Game::getRenderer()), pos,
                 Vector2D<int>(0, 0)),
      font_(font),
      color_(color) {
  setText(text, {0, 0, 0, 255}, lineJumpLimit);
}

Text::~Text() {
  delete texture_;
  texture_ = nullptr;
}

void Text::setText(const std::string& text, const SDL_Color& color,
                   int lineJumpLimit) {
  text_ = text;
  texture_->loadFromText(font_, text, color, lineJumpLimit);
  size_.set(texture_->getSize().getX(), texture_->getSize().getY());
}

void Text::setColor(const SDL_Color& color) {
  color_ = color;
  texture_->loadFromText(font_, text_, color);
  size_.set(texture_->getSize().getX(), texture_->getSize().getY());
}

void Text::render() const {
    const auto rect = getRect();
  SDL_RenderCopy(Game::getRenderer(), texture_->getTexture(), nullptr,
                 &rect);
}

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Font.h"

#include "../Errors/SDLError.h"

Font::Font() = default;

Font::Font(const std::string& filename, const int size) {
  load(filename, size);
}

Font::~Font() { close(); }

void Font::close() {
  if (font_) {
    TTF_CloseFont(font_);
    font_ = nullptr;
  }
}

Font* Font::load(const std::string& filename, const int size) {
  font_ = TTF_OpenFont(filename.c_str(), size);
  if (font_ == nullptr) {
    const auto message =
        "Error loading font from " + filename + "\nReason: " + TTF_GetError();
    throw SDLError(message);
  }
  return this;
}

SDL_Surface* Font::renderText(const std::string& text, const SDL_Color color,
                              const int lineJumpLimit) const {
  if (font_ == nullptr) return nullptr;
  return TTF_RenderUTF8_Blended_Wrapped(font_, text.c_str(), color,
                                        lineJumpLimit);
}

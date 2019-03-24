// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>
#include "SDL_ttf.h"

class Font {
 private:
  TTF_Font* font_;

 public:
  Font();
  Font(std::string filename, int size);
  ~Font();

  TTF_Font* getFont() const { return font_; }
  Font* load(std::string filename, int size);
  void close();
  SDL_Surface* renderText(std::string text, SDL_Color color,
                          int lineJumpLimit) const;
};

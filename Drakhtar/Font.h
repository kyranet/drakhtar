// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "SDL_ttf.h"
#include <string>
#include "checkML.h"

using namespace std;

class Font
{
 private:
    TTF_Font* font_;

 public:
    Font();
    Font(string filename, int size);
    ~Font();

    TTF_Font* getFont() const { return font_; }
    Font* load(string filename, int size);
    void close();
    SDL_Surface* renderText(string text, SDL_Color color, int lineJumpLimit) const;
};

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Font.h"
#include "SDLError.h"

Font::Font() : font_(nullptr) {}

Font::Font(string filename, int size)
{
    load(filename, size);
}

Font::~Font()
{
    close();
}

void Font::close()
{
    if (font_)
    {
        TTF_CloseFont(font_);
        font_ = nullptr;
    }
}

Font *Font::load(string filename, int size)
{
    font_ = TTF_OpenFont(filename.c_str(), size);
    if (font_ == nullptr)
    {
        string message = "Error loading font from " + filename + "\nReason: " + TTF_GetError();
        throw new SDLError(message);
    }
    return this;
}

SDL_Surface* Font::renderText(string text, SDL_Color color, int lineJumpLimit) const
{
    if (font_ == nullptr)
    return nullptr;
    // return TTF_RenderText_Blended(font_, text.c_str(), color);
    return TTF_RenderText_Blended_Wrapped(font_, text.c_str(), color, lineJumpLimit);
}

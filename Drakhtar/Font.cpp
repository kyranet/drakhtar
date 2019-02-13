#include "Font.h"

Font::Font(SDL_Renderer* renderer, string filename, int size) : renderer(renderer), size(size)
{
	load(filename);
}

Font::~Font()
{
	liberate();
}

TTF_Font *Font::getFont() const
{
	return font;
}

SDL_Renderer *Font::getRenderer() const
{
	return renderer;
}

void Font::liberate()
{
	TTF_CloseFont(font);
	font = nullptr;
}

void Font::load(string filename)
{
	font = TTF_OpenFont(filename.c_str(), size);
}

#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "Texture.h"
#include "checkML.h"

class Font
{
private:
	TTF_Font* font = nullptr;
	SDL_Renderer* renderer;
	uint size = 8;

public:
	Font(SDL_Renderer* renderer, string filename, int size);
	~Font();
	TTF_Font* getFont() const;
	SDL_Renderer* getRenderer() const;
	void liberate();
	void load(string filename);
};

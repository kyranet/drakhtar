#pragma once

#include "checkML.h"
#include "SDL.h"       // Windows
#include "SDL_image.h" // Windows

#include <string>

using namespace std;

typedef unsigned int uint;

class Texture
{
private:
	SDL_Texture *_texture = nullptr;
	SDL_Renderer *_renderer = nullptr;
	uint _w = 0;
	uint _h = 0;
	uint _fw = 0; // Frame width
	uint _fh = 0; // Frame height
	uint _numCols = 1;
	uint _numRows = 1;

public:
	Texture(SDL_Renderer *r) : _renderer(r) {};
	Texture(SDL_Renderer *r, string filename, uint numRows = 1, uint numCols = 1) : _renderer(r) { load(filename, numRows, numCols); };
	Texture(SDL_Texture *texture, SDL_Renderer *renderer, uint w, uint h, uint fw, uint fh, uint numRows, uint numCols);
	~Texture() { liberate(); };
	void liberate();

	int getW() const { return _w; };
	int getH() const { return _h; };
	uint getNumCols() const { return _numCols; };
	uint getNumRows() const { return _numRows; };
	void setTexture(SDL_Texture *texture)
	{
		if (texture != _texture)
		{
			SDL_DestroyTexture(_texture);
			_texture = texture;
		}
	}
	SDL_Texture *getTexture() const { return _texture; };

	void load(string filename, uint numRows = 1, uint numCols = 1);
	void render(const SDL_Rect &rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void renderFrame(const SDL_Rect &destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};
#pragma once

#include "checkML.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Font.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef unsigned int uint;
typedef unsigned short ushort;

class Texture
{
private:
	SDL_Texture *texture_ = nullptr;
	SDL_Renderer *renderer_ = nullptr;
	Vector2D<ushort> size_;
	Vector2D<ushort> frameSize_;
	uint columnAmount_ = 1;
	uint rowAmount_ = 1;
	map<string, vector<ushort>> animations_;

public:
	Texture() {};
	Texture(SDL_Renderer *r) : renderer_(r) {};
	virtual ~Texture();

	ushort getColumnAmount() const { return columnAmount_; }
	ushort getRowAmount() const { return rowAmount_; }
	Vector2D<ushort> getSize() const { return size_; }
	Vector2D<ushort> getFrameSize() const { return frameSize_; }
	Vector2D<ushort> getFramePosition(ushort frame) const { return Vector2D<ushort>(frame % columnAmount_, (ushort)floor(frame / columnAmount_)); };
	SDL_Texture* getTexture() const { return texture_; }
	SDL_Renderer* getRenderer() const { return renderer_; }

	Texture* setTexture(SDL_Texture* texture);
	Texture* setColumnAmount(ushort columns);
	Texture* setRowAmount(ushort rows);
	Texture* setFrameSize(Vector2D<ushort> frameSize);
	Texture* loadFromImage(string filename, ushort rowAmount = 1, ushort columnAmount = 1);
	Texture* loadFromText(Font* font, string text, SDL_Color const color = { 0, 0, 0, 255 });
	void addAnimation(string name, vector<ushort> frames);
	bool hasAnimation(string name);
	void render(Vector2D<int> position) const;
	void render(SDL_Rect const& dest, double angle = 0, SDL_Rect* clip = nullptr) const;
	void renderFrame(SDL_Rect const& dest, ushort frame, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void close();
};
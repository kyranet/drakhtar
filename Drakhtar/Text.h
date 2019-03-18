#pragma once

#include "Font.h"
#include "GameObject.h"
#include "checkML.h"
#include <iostream>

class Text : public GameObject
{
private:
	Font* font_;
	Texture* texture_;
	string text_;
	SDL_Color color_;

public:
	Text(SDL_Renderer* renderer, Font* font, Vector2D<int> pos, SDL_Color &color, string &text, int lineJumpLimit);
	~Text();
	void setText(string const text, SDL_Color const color = { 0, 0, 0, 255 }, int lineJumpLimit = 250);
	void setPos(int x, int y);
	void setColor(SDL_Color const color);
	void render() const;
};
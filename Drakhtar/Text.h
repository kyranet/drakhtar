#pragma once

#include "checkML.h"
#include "Font.h"
#include "GameObject.h"

class Text : public GameObject
{
private:
	Font *font;
	Texture *texture;
	string text;
	SDL_Color color;
	int width, height;

public:
	Text(Font *font, int x, int y, int width, int height, const SDL_Color &color, const string &text);
	~Text();
	void setText(string newText);
	SDL_Color setColor(const SDL_Color &color);
	SDL_Rect getDestRect() const;
	void render() const;
};
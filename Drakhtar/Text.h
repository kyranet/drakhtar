#pragma once

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
	Text(Font* font, vector2d pos, vector2d size, SDL_Color &color, string &text);
	~Text();
	void setText(string newText);
	void setColor(SDL_Color &color);
	SDL_Rect getDestRect() const;
	void render() const;
};
#pragma once

#include "Font.h"
#include "GameObject.h"

class Text : public GameObject
{
private:
	Font* font_;
	Texture* texture_;
	string text_;
	SDL_Color color_;

public:
	Text(Font* font, vector2d pos, vector2d size, SDL_Color &color, string &text);
	~Text();
	void setText(const string newText);
	void setColor(const SDL_Color &color);
	void render() const;
};
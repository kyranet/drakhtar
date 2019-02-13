#include "Text.h"

Text::Text(Font* font, vector2d pos, vector2d size, SDL_Color &color, string &text)
	: GameObject(nullptr, pos, size), font(font), color(color), text(text)
{
}

Text::~Text()
{
}

void Text::setText(string newText) {}
void Text::setColor(SDL_Color &color) {}
SDL_Rect Text::getDestRect() const
{
	return {
		width,
		height
	};
}
void Text::render() const {}

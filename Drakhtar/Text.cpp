#include "Text.h"

Text::Text(Font* font, int x, int y, int width, int height, SDL_Color &color, string &text)
	:font(font), GameObject(x, y, width, height), color(color), text(text)
{
}

Text::~Text()
{
}

#include "Text.h"

Text::Text(SDL_Renderer* renderer, Font* font, Vector2D<int> pos, Vector2D<int> size, SDL_Color &color, string &text)
// fix nullptr
	: GameObject(nullptr, pos, size), font_(font), color_(color)
{
	texture_ = new Texture(renderer);
	setText(text);
}

Text::~Text()
{
	delete texture_;
}

void Text::setText(string const text, SDL_Color const color)
{
	text_ = text;
	texture_->loadFromText(font_, text, color);
}

void Text::setColor(SDL_Color const color)
{
	color_ = color;
	texture_->loadFromText(font_, text_, color);
}

void Text::render() const
{
	SDL_RenderCopy(texture_->getRenderer(), texture_->getTexture(), nullptr, &getRect());
}

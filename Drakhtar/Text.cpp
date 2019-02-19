#include "Text.h"

Text::Text(SDL_Renderer* renderer, Font* font, Vector2D<int> pos, SDL_Color &color, string &text)
	: GameObject(nullptr, pos, Vector2D<int>(0, 0)), font_(font), color_(color)
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
	size_.set(texture_->getSize().getX(), texture_->getSize().getY());
}

void Text::setColor(SDL_Color const color)
{
	color_ = color;
	texture_->loadFromText(font_, text_, color);
	size_.set(texture_->getSize().getX(), texture_->getSize().getY());
}

void Text::render() const
{
	SDL_RenderCopy(texture_->getRenderer(), texture_->getTexture(), nullptr, &getRect());
}

#include "Text.h"

Text::Text(SDL_Renderer* renderer, Font* font, Vector2D<int> pos, SDL_Color &color, string &text, int lineJumpLimit)
	: GameObject(nullptr, pos, Vector2D<int>(0, 0)), font_(font), color_(color)
{
	texture_ = new Texture(renderer);
	setText(text, { 0, 0, 0, 255 }, lineJumpLimit);
}

Text::~Text()
{
	delete texture_;
}

void Text::setText(string const text, SDL_Color const color, int lineJumpLimit)
{
	text_ = text;
	texture_->loadFromText(font_, text, color, lineJumpLimit);
	size_.set(texture_->getSize().getX(), texture_->getSize().getY());
}

void Text::setPos(int x, int y)
{
	pos_.setX(x);
	pos_.setY(y);
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

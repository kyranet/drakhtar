#include "Text.h"

Text::Text(Font* font, vector2d pos, vector2d size, SDL_Color &color, string &text)
// fix nullptr
	: GameObject(nullptr, pos, size), font_(font), color_(color)
{
	setText(text);
}

Text::~Text()
{
	delete texture_;
}

void Text::setText(const string newText)
{
	text_ = newText;
	TTF_SizeText(font_->getFont(), newText.c_str(), &size_.x, &size_.y);
	SDL_Surface *textSurface = TTF_RenderText_Solid(font_->getFont(), newText.c_str(), color_);
	texture_->setTexture(SDL_CreateTextureFromSurface(font_->getRenderer(), textSurface));
	SDL_FreeSurface(textSurface);
}

void Text::setColor(const SDL_Color &color)
{
	SDL_Surface *textSurface = TTF_RenderText_Solid(font_->getFont(), text_.c_str(), color);
	texture_->setTexture(SDL_CreateTextureFromSurface(font_->getRenderer(), textSurface));
	SDL_FreeSurface(textSurface);
	color_ = color;
}

void Text::render() const
{
	SDL_RenderCopy(font_->getRenderer(), texture_->getTexture(), nullptr, &getRect());
}

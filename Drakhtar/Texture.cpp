#include "Texture.h"
#include <iostream>
#include "SDLError.h"

using namespace std;

Texture::~Texture()
{
	close();
}

Texture* Texture::setTexture(SDL_Texture* texture)
{
	if (texture != texture_)
	{
		if (texture_ != nullptr) SDL_DestroyTexture(texture_);
		texture_ = texture;
	}

	return this;
}

Texture* Texture::setColumnAmount(ushort columns)
{
	columnAmount_ = columns;
	return this;
}

Texture* Texture::setRowAmount(ushort rows)
{
	rowAmount_ = rows;
	return this;
}

Texture* Texture::setFrameSize(Vector2D<ushort> frameSize)
{
	frameSize_ = frameSize;
	return this;
}

Texture* Texture::loadFromImage(string filename, ushort rowAmount, ushort columnAmount)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr)
	{
		throw new SDLError("Error loading surface from " + filename);
	}

	close();
	texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
	if (texture_ != nullptr)
	{
		size_.set(surface->w, surface->h);
		frameSize_.set(surface->w / columnAmount, surface->h / rowAmount);
		columnAmount_ = columnAmount;
		rowAmount_ = rowAmount;
	}
	SDL_FreeSurface(surface);
	return this;
}

Texture* Texture::loadFromText(Font* font, string text, SDL_Color const color)
{
	SDL_Surface* surface = font->renderText(text, color);
	if (surface == nullptr)
	{
		throw new SDLError("Error loading text: " + text);
	}

	close();
	texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
	if (texture_ != nullptr)
	{
		size_.set(surface->w, surface->h);
		frameSize_.set(surface->w, surface->h);
		columnAmount_ = 1;
		rowAmount_ = 1;
	}
	SDL_FreeSurface(surface);
	return this;
}

void Texture::render(Vector2D<int> position) const
{
	SDL_Rect dest{ position.getX(), position.getY(), size_.getX(), size_.getY() };
	render(dest);
}

void Texture::render(SDL_Rect const& dest, double angle, SDL_Rect* clip) const
{
	if (texture_ != nullptr)
	{
		if (clip == nullptr) {
			SDL_Rect default_clip = { 0, 0, size_.getX(), size_.getY() };
			clip = &default_clip;
		}
		SDL_RenderCopy(renderer_, texture_, clip, &dest);
	}
}

void Texture::renderFrame(SDL_Rect const& dest, ushort frame, double angle, SDL_RendererFlip flip) const
{
	auto framePosition = getFramePosition(frame);
	ushort width = frameSize_.getX();
	ushort heigth = frameSize_.getY();
	SDL_Rect src{
		width * framePosition.getX(),
		heigth * framePosition.getY(),
		width,
		heigth
	};
	SDL_RenderCopyEx(renderer_, texture_, &src, &dest, angle, 0, flip);
}

void Texture::close()
{
	if (texture_ != nullptr)
	{
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
		size_.set(0, 0);
	}
}

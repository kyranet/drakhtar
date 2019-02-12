#pragma once

#include "GameObject.h"

GameObject::GameObject(Texture* texture, double pos_x, double pos_y, double size_x, double size_y)
	: texture_(texture), pos_x(pos_x), pos_y(pos_y), size_x(size_x), size_y(size_y)
{
}


GameObject::~GameObject()
{
	texture_ = nullptr;
}

void GameObject::render() const
{
	texture_->render({ (int)pos_x - (int)size_x / 2, (int)pos_y - (int)size_y / 2, (int)size_x, (int)size_y });
}

void GameObject::handleEvents(SDL_Event event)
{
}

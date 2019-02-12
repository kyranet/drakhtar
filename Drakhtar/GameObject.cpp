#pragma once

#include "GameObject.h"

GameObject::~GameObject()
{
	texture_ = nullptr;
}

void GameObject::render() const
{
	texture_->render({ (int)pos_.x - (int)size_.x / 2, (int)pos_.y - (int)size_.y / 2, (int)size_.x, (int)size_.y });
}

void GameObject::handleEvents(SDL_Event event)
{
}

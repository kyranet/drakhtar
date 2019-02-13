#pragma once

#include "GameObject.h"

GameObject::~GameObject()
{
	texture_ = nullptr;
	for (auto listener : eventListeners_)
		delete listener;
	eventListeners_.clear();
}

void GameObject::render() const
{
	texture_->render({ (int)pos_.x - (int)size_.x / 2, (int)pos_.y - (int)size_.y / 2, (int)size_.x, (int)size_.y });
}

void GameObject::handleEvents(SDL_Event event)
{
	for (auto listener : eventListeners_)
		listener->run(event);
}

GameObject* GameObject::addEventListener(EventListener* eventListener)
{
	eventListeners_.push_back(eventListener);
	return this;
};

SDL_Rect GameObject::getRect() const
{
	return {
		pos_.x,
		pos_.y,
		size_.x,
		size_.y
	};
}

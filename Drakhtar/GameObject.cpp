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
	texture_->render({ pos_.getX() - size_.getX() / 2, pos_.getY() - size_.getY() / 2, size_.getX(), size_.getY() });
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
		pos_.getX(),
		pos_.getY(),
		size_.getX(),
		size_.getY()
	};
}

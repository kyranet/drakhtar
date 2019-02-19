#pragma once

#include "Texture.h"
#include "EventListener.h"
#include "Vector2D.h"
#include <list>

class EventListener;

class GameObject
{
protected:
	Vector2D<int> pos_;
	Vector2D<int> size_;
	Texture* texture_;
	list<EventListener*> eventListeners_;
public:
	GameObject(Texture* texture, Vector2D<int> pos, Vector2D<int> size)
		: texture_(texture), pos_(pos), size_(size) {}
	// TODO: Remove this after all operations use the vector2d approach
	GameObject(Texture* texture, int pos_x, int pos_y, int size_x, int size_y)
		: texture_(texture), pos_(Vector2D<int>(pos_x, pos_y)), size_(Vector2D<int>(size_x, size_y)) {};
	virtual ~GameObject();
	virtual void render() const;
	virtual void handleEvents(SDL_Event event);
	GameObject* addEventListener(EventListener* eventListener);
	SDL_Rect getRect() const;
};

#pragma once

#include "Texture.h"
#include "EventListener.h"
#include <list>

struct vector2d {
	int x;
	int y;
};

class EventListener;

class GameObject
{
protected:
	vector2d pos_;
	vector2d size_;
	Texture* texture_;
	list<EventListener*> eventListeners_;
public:
	GameObject(Texture* texture, vector2d pos, vector2d size)
		: texture_(texture), pos_(pos), size_(size) {}
	virtual ~GameObject();
	virtual void render() const;
	virtual void handleEvents(SDL_Event event);
	GameObject* addEventListener(EventListener* eventListener);
	SDL_Rect getRect() const;
};


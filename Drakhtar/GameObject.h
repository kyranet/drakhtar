#pragma once

#include "Texture.h"
#include "EventListener.h"
#include <list>

struct vector2d {
	float x;
	float y;
};

class EventListener;

class GameObject
{
private:
	vector2d pos_;
	vector2d size_;
	Texture* texture_;
protected:
	list<EventListener*> eventListeners_;
public:
	GameObject(Texture* texture, vector2d pos, vector2d size)
		: texture_(texture), pos_(pos), size_(size) {}
	// TODO: Remove this after all operations use the vector2d approach
	GameObject(Texture* texture, float pos_x, float pos_y, float size_x, float size_y)
		: texture_(texture), pos_(vector2d{ pos_x, pos_y }), size_(vector2d{ size_x, size_y }) {};
	~GameObject();
	virtual void render() const;
	virtual void handleEvents(SDL_Event event);
	GameObject* addEventListener(EventListener* eventListener);
	SDL_Rect getRect() const;
};


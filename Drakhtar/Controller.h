#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "EventListener.h"
#include "Board.h"

class Controller : public EventListener
{
public:
	Controller(GameObject* gameObject)
		: EventListener(gameObject) {};
	virtual void run(SDL_Event event);
	void onHover(bool onTop);
	void onClick(bool onTop, SDL_Point p);
};

#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "EventListener.h"

class Controller : public EventListener
{
private:
	bool mouseOn = false;
public:
	Controller(GameObject* gameObject)
		: EventListener(gameObject) {};
	virtual void handleEvents(SDL_Event event);
	void onHover(bool mouseOn);
	void onClick(bool mouseOn);
};


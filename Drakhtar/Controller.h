#pragma once

#include "SDL.h"
#include "GameObject.h"

class Controller
{
private:
	GameObject* gameObject_;
	bool mouseOn = false;
public:
	Controller(GameObject* gameObject);
	virtual ~Controller();
	void handleEvents(SDL_Event event);
	void onHover(bool mouseOn);
	void onClick(bool mouseOn);
};


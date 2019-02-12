#pragma once

#include "SDL.h"
#include "GameObject.h"

struct Keybinds {
	SDL_Keycode up;
	SDL_Keycode down;
	SDL_Keycode left;
	SDL_Keycode right;
};

class Controller
{
private:
	GameObject* gameObject_;
	Keybinds keybinds_;
public:
	Controller(GameObject* gameObject, Keybinds keybinds);
	virtual ~Controller();
	void handleEvents(SDL_Event event);
};


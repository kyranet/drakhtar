#pragma once

#include "SDL.h"
#include "EventListener.h"
#include "DialogScene.h"

class DialogController : public EventListener
{
private:
	DialogScene * dialogScene_;
public:
	DialogController(DialogScene* dialogScene);
	virtual void run(SDL_Event event);
	void onClick(SDL_Point p);
};


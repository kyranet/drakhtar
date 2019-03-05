#pragma once

class EventListener
{
public:
	EventListener() {};
	virtual ~EventListener() {};
	virtual void run(SDL_Event event) = 0;
};

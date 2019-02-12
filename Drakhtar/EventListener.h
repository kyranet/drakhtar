#pragma once

class EventListener
{
protected:
	GameObject* gameObject_;
public:
	EventListener(GameObject* gameObject)
		: gameObject_(gameObject) {};
	virtual ~EventListener() { gameObject_ = nullptr; };
	virtual void handleEvents(SDL_Event event) = 0;
};


#pragma once

#include "GameObject.h"

class GameObject;

class EventListener
{
protected:
	GameObject* gameObject_;
public:
	EventListener(GameObject* gameObject)
		: gameObject_(gameObject) {};
	virtual ~EventListener() { gameObject_ = nullptr; };
	virtual void run(SDL_Event event) = 0;
};


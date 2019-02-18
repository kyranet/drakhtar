#include "Controller.h"
#include <iostream>
void Controller::run(SDL_Event event)
{
	SDL_Point p= { event.motion.x, event.motion.y };
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		
		//std::cout << event.motion.x << " " << event.motion.y << endl;
		//onHover(SDL_PointInRect(&p,&gameObject_->getRect()));			
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) {
			
			onClick(SDL_PointInRect(&p, &gameObject_->getRect()), p);
		}
		break;
	default:
		break;
	}
}

void Controller::onHover(bool onTop)
{
	// ilumina
}

void Controller::onClick(bool onTop, SDL_Point p)
{
	if (onTop) // if true, mouse position = gameobject position
	{
		std::cout << "clickado";
	}
		// Mover/Atacar
}

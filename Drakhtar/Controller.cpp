#include "Controller.h"

void Controller::run(SDL_Event event)
{
	SDL_Point p;
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		p = { event.motion.x, event.motion.y };
		onHover(SDL_PointInRect(&p,&gameObject_->getRect()));
		break;
	default:
		break;
	}
}

void Controller::onHover(bool mouseOn)
{
	// ilumina
}

void Controller::onClick(bool mouseOn)
{
	if (mouseOn)
	{
		// Seleccionar y deseleccionar unidad
	}
	else
	{
		// Mover/Atacar
	}
}

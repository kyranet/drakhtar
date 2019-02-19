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
			onClick(SDL_PointInRect(&p, &gameObject_->getRect()), p); // checks with gameObject
		}
		break;
	default:
		break;
	}
}

void Controller::onHover(bool onTop)	
{
	// ilumina
	std::cout << "clickado2 ";
}

void Controller::onClick(bool onTop, SDL_Point p) // cambiar el nombre de este metodo para su funcion, mas adelante
{
	if (onTop) // if true, mouse position = gameobject position
	{
		Box * box = static_cast<Box*>(gameObject_);
		//idea para implementacion, hacer un metodo en unit o board? para que se seleccione la unidad clickada, o deseleccionar si se vuelve a clickar en ella
		//una vez seleccionada, podremos moverlo mirando el mousemotion y cuando clicka en una casilla se mira si se tiene una unidad seleccionada y si da true, mirara si la unidad puede moverse,
		// tambien comprueba si donde clicka hay obstaculo o un enemigo o aliado, en caso de curar a una unidad
		std::cout << " clickado " <<box->getRect().x << " " << box->getRect().y << " " << box->getRect().w << " " << box->getRect().h;
	}
		// Mover/Atacar
}

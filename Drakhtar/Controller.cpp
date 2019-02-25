#include "Controller.h"
#include <iostream>

void Controller::run(SDL_Event event) {
	SDL_Point p= { event.motion.x, event.motion.y };
	switch (event.type) {
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

void Controller::onHover(bool onTop) {
	// ilumina
	std::cout << "clickado2 ";
}

// cambiar el nombre de este metodo para su funcion, mas adelante
void Controller::onClick(bool onTop, SDL_Point p) {
	if (onTop) // if true, mouse position = gameobject position
	{
		Box * box = static_cast<Box*>(gameObject_);
		if (box->getContent() == nullptr) {
			// TODO Check movement range here
			std::cout << "Moving to cell (" << box->getIndex().getX() << ", " << box->getIndex().getY() << ")" << endl;
		} else {
			/* TODO
			if(occupied by an ally) {
				// Do nothing unless de unit is a healer
			} else if(occupied by an enemy) {
				// Move to an adjacent box and attack him
			}
			*/
			std::cout << "Cell (" << box->getIndex().getX() << ", " << box->getIndex().getY() << ") is occupied" << endl;
		}
	}
}

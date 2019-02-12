#include "Controller.h"



Controller::Controller(GameObject* gameObject, Keybinds keybinds)
	: gameObject_(gameObject), keybinds_(keybinds)
{
}


Controller::~Controller()
{
	gameObject_ = nullptr;
}

void Controller::handleEvents(SDL_Event event)
{

}

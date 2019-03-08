#include "DialogController.h"


DialogController::DialogController(DialogScene * dialogScene) : dialogScene_(dialogScene)
{
}

void DialogController::run(SDL_Event event)
{
	SDL_Point p = { event.motion.x, event.motion.y };

	switch (event.type) {
	case SDL_MOUSEBUTTONUP:
		onClick(p);
		break;
	}
}

void DialogController::onClick(SDL_Point p)
{
	GameObject * dialogBlock = dialogScene_->getBlockSprite();

	if (p.x >= dialogBlock->getRect().x && p.y >= dialogBlock->getRect().y &&
		p.x <= dialogBlock->getRect().x + dialogBlock->getRect().w && p.y <= dialogBlock->getRect().y + dialogBlock->getRect().h)
	{
		dialogScene_->nextDialog();
	}
}

#include "DialogController.h"

DialogController::DialogController(DialogScene * dialogScene) : dialogScene_(dialogScene)
{
}

void DialogController::run(SDL_Event event)
{
	SDL_Point p = { event.motion.x, event.motion.y };

	switch (event.type) {
	case SDL_MOUSEBUTTONUP:
		if (!endOfDialog_)
			onClick(p);
		break;
	}
}

void DialogController::onClick(SDL_Point p)
{
	GameObject* dialogBlock = dialogScene_->getBlockSprite();
	SDL_Rect *rect = &dialogBlock->getRect();

	if (SDL_PointInRect(&p, rect) && !endOfDialog_) {
		dialogScene_->nextDialog();
		if (dialogScene_->isEndOfDialog())
			endOfDialog_ = true;
	}
}

SDL_bool DialogController::SDL_PointInRect(SDL_Point* p, SDL_Rect* r)
{
	if (p->x >= r->x && p->y >= r->y && p->x <= r->x + r->w && p->y <= r->y + r->h)
		return SDL_bool(true);
	else
		return SDL_bool(false);
}

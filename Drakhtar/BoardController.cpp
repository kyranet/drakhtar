#include "BoardController.h"
#include <iostream>

BoardController::BoardController(Board * board, TurnBar * turnBar) :
	board_(board), turnBar_(turnBar) { }

void BoardController::run(SDL_Event event) {
	SDL_Point p= { event.motion.x, event.motion.y };

	switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			onClick(p);
			break;
		case SDL_MOUSEMOTION:
			onHover(p);
			break;
	}
}

void BoardController::onClick(SDL_Point p) {
	Box * boxClicked = board_->getBoxAtCoordinates(Vector2D<int>(p.x, p.y));

	if (boxClicked != nullptr) {
		if (boxClicked->getContent() == nullptr) {
			turnBar_->getFrontUnit()->moveToBox(boxClicked);
			turnBar_->advanceTurn();
		}
	}
}

void BoardController::onHover(SDL_Point p) {
	Box * boxHovered = board_->getBoxAtCoordinates(Vector2D<int>(p.x, p.y));

	if (boxHovered != nullptr) {
		boxHovered->setHovered(true);
	}
}
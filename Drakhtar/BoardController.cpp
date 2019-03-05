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
	}
}

void BoardController::onClick(SDL_Point p) {
	Box * boxClicked = board_->getBoxAtCoordinates(Vector2D<int>(p.x, p.y));

	// Checks if the box clicked exists and is empty
	if (boxClicked != nullptr && boxClicked->isEmpty()) {
		Unit* activeUnit = turnBar_->getFrontUnit();
		if (board_->isInRange(activeUnit->getBox(), boxClicked, activeUnit->getMoveRange())) {
			activeUnit->moveToBox(boxClicked);
			turnBar_->advanceTurn();
		}
		else { cout << "Out of movement range!" << endl; }
	}
}

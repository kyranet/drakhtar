#include "BoardController.h"
#include <iostream>

BoardController::BoardController(Board * board, TurnBar * turnBar) :
	board_(board), turnBar_(turnBar) { }

void BoardController::run(SDL_Event event) {
	SDL_Point p= { event.motion.x, event.motion.y };

	switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (moving) {
				onClickMove(p);
			} else {
				onClickAttack(p);
			}
			break;
	}
}

void BoardController::onClickMove(SDL_Point p) {
	Box * boxClicked = board_->getBoxAtCoordinates(Vector2D<int>(p.x, p.y));

	// Checks if the box clicked exists and is empty
	if (boxClicked != nullptr && boxClicked->isEmpty()) {
		Unit* activeUnit = turnBar_->getFrontUnit();

		// Checks if the box clicked is within movement range
		if (board_->isInRange(activeUnit->getBox(), boxClicked, activeUnit->getMoveRange())) {
			activeUnit->moveToBox(boxClicked);

			// If there are enemies nearby enable attack, if not end turn
			if (board_->isEnemyInRange(boxClicked, activeUnit->getMoveRange())) {
				moving = false;
			} else {
				turnBar_->advanceTurn();
			}
		}
		else { cout << "Out of movement range!" << endl; }
	}
}

void BoardController::onClickAttack(SDL_Point p) {
	cout << "ATTACK" << endl;
}
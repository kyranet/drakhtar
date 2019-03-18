// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "BoardController.h"
#include <iostream>

BoardController::BoardController(Board *board, TurnBar *turnBar) : board_(board), turnBar_(turnBar) {}

void BoardController::run(SDL_Event event) {
    activeUnit_ = turnBar_->getFrontUnit();
    if (moving) {
        board_->highlightCellsInRange(activeUnit_->getBox(), activeUnit_->getMoveRange());
    } else {
		board_->highlightEnemiesInRange(activeUnit_->getBox(), activeUnit_->getAttackRange());
	}

    switch (event.type) {
    case SDL_MOUSEBUTTONUP:
        SDL_Point p = {event.motion.x, event.motion.y};
        if (moving) {
            onClickMove(p);
        } else {
            onClickAttack(p);
        }
        break;
    }
}

void BoardController::onClickMove(SDL_Point p)
{
    Box *boxClicked = board_->getBoxAtCoordinates(Vector2D<int>(p.x, p.y));

    // Checks if the box clicked exists and is empty
    if (boxClicked != nullptr && boxClicked->isEmpty())  {
        // Checks if the box clicked is within movement range
        if (board_->isInRange(activeUnit_->getBox(), boxClicked, activeUnit_->getMoveRange())) {
            activeUnit_->moveToBox(boxClicked);

            // If there are enemies nearby enable attack, if not end turn
            if (board_->isEnemyInRange(boxClicked, activeUnit_->getAttackRange())) {
                moving = false;
            } else {
                turnBar_->advanceTurn();
            }
			board_->resetCellsToBase();
        } else {
            cout << "Out of movement range!" << endl;
        }
    }
}

void BoardController::onClickAttack(SDL_Point p) {
    Box *boxClicked = board_->getBoxAtCoordinates(Vector2D<int>(p.x, p.y));
    if (boxClicked != nullptr && !boxClicked->isEmpty()) {
        // Box clicked exists and is not empty
        if (boxClicked->getContent()->getTeam() != activeUnit_->getTeam() &&						// Unit clicked if from a different team and
			board_->isInRange(activeUnit_->getBox(), boxClicked, activeUnit_->getAttackRange()))	// Unit clicked is in range
        {
            boxClicked->getContent()->loseHealth(activeUnit_->getAttack());  // Attack
            moving = true;                                                   // Re-enable movement
            turnBar_->advanceTurn();                                         // End turn
			board_->resetCellsToBase();
        }
    }
}

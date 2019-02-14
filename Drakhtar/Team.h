#pragma once

#include <list>
#include "Unit.h"
#include "Board.h"

class Unit;

// TODO: Replace GameObject with Unit once they are done
// TODO: Implement turns logic

class Team
{
private:
	list<Unit*> units_;
	Board* board_ = nullptr;
public:
	Team(Board* board);
	virtual ~Team();
	Board* getBoard() { return board_; }
	void addUnit(Unit* unit);
	void removeUnit(Unit* unit);
};

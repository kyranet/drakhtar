#pragma once

#include <list>
#include "GameObject.h"
#include "Board.h"

// TODO: Replace GameObject with Unit once they are done
// TODO: Implement turns logic

class Team
{
private:
	list<GameObject*> units_;
	Board* board_ = nullptr;
public:
	Team(Board* board);
	virtual ~Team();
	Board* getBoard() { return board_; }
	void addUnit(GameObject* unit);
	void removeUnit(GameObject* unit);
};

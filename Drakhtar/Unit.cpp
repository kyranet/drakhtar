#include "Unit.h"

void Unit::moveTowards(vector2d pos)
{
	// If it's not the unit's turn, cancel any action
	if (!moving_) return;

	// TODO: Do any logic here, interact with the Board
	// TODO: Maybe Unit->Team->Board?
}

void Unit::setMoving(bool moving)
{
	moving_ = moving;
}

void Unit::setMoved(bool moved)
{
	moved_ = moved;
}

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

void Unit::setBoxPosition(vector2d position)
{
	boxPosition_ = position;
	// FIXME: Set the GameObject's position by calculating
	// the coordinates in pixels of the box, or maybe
	// make this method take two arguments and pass both
	// together.
}

void Unit::setTeam(Team* team)
{
	team_ = team;
}

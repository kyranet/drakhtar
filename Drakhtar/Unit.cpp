#include "Unit.h"

Unit::Unit(Texture* texture, Box * box, int attack, int health, int speed, int attackRange, int moveRange)
	: GameObject(texture, 
		Vector2D<int>(box->getRect().x + box->getRect().w / 2, box->getRect().y + box->getRect().h / 2), 
		Vector2D<int>(box->getRect().w, box->getRect().h)), attack_(attack), health_(health), speed_(speed), 
		attackRange_(attackRange), moveRange_(moveRange), box_(box)
{
	box->setContent(this);
}

void Unit::moveTowards(Vector2D<int> pos) {
	// If it's not the unit's turn, cancel any action
	if (!moving_) return;

	// TODO: Do any logic here, interact with the Board
	// TODO: Maybe Unit->Team->Board?
}

void Unit::setMoving(bool moving) {
	moving_ = moving;
}

void Unit::setMoved(bool moved) {
	moved_ = moved;
}

void Unit::setBoxPosition(Vector2D<int> position) {
	boxPosition_ = position;
	// FIXME: Set the GameObject's position by calculating
	// the coordinates in pixels of the box, or maybe
	// make this method take two arguments and pass both
	// together.
	setMoved(true);
}

void Unit::setTeam(Team* team) {
	team_ = team;
}

void Unit::moveToBox(Box * newBox) {
	box_->setContent(nullptr);
	pos_ = Vector2D<int>(newBox->getRect().x, newBox->getRect().y);
	newBox->setContent(this);
}

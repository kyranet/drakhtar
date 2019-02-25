#include "Battalion.h"



Battalion::~Battalion()
{
}

void Battalion::setBattalionSize(int battalionSize)
{
	battalionSize_ = battalionSize;
}

int Battalion::getAttack() const
{
	return Unit::getAttack() * battalionSize_;
}

int Battalion::getMaxHealth() const
{
	return Unit::getMaxHealth() * battalionSize_;
}

void Battalion::loseHealth(int health)
{
	if (Unit::getMaxHealth() <= health) {
		battalionSize_ -= health / Unit::getMaxHealth();
		if (battalionSize_ < 0)
			battalionSize_ = 0;
	}
	Unit::loseHealth(health);

}

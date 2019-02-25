#pragma once
#include "Unit.h"
class Battalion :
	public Unit
{
private:
	int battalionSize_;

public:
	Battalion(Texture* texture, Box * box, int attack, int health, int speed, int attackRange, int moveRange, int battalionSize)
		: Unit(texture, box, attack, health, speed, attackRange, moveRange), battalionSize_(battalionSize) {}
	virtual ~Battalion();

	int getBattalionSize() const { return battalionSize_; }
	void setBattalionSize(int battalionSize);

	virtual int getAttack() const;
	virtual int getMaxHealth() const;

	virtual void loseHealth(int health);
};


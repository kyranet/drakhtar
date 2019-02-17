#pragma once
#include "Unit.h"
class Battalion :
	public Unit
{
private:
	int battalionSize_;

public:
	Battalion(Texture* texture, Vector2D<int> pos, Vector2D<int> size, int attack, int defense, int maxHealth, int speed, int attackRange, int moveRange, int battalionSize)
		: Unit(texture, pos, size, attack, defense, maxHealth, speed, attackRange, moveRange), battalionSize_(battalionSize) {}
	virtual ~Battalion();

	int getBattalionSize() const { return battalionSize_; }
	int setBattalionSize(int battalionSize);

	virtual int getAttack() const;
	virtual int getDefense() const;
	virtual int getMaxHealth() const;

	virtual void loseHealth(int health);
};


#pragma once

#include "GameObject.h"
#include "Team.h"
#include "Box.h"

class Team;

class Unit : public GameObject
{
private:
	int attack_;
	int defense_;
	int health_;
	int maxHealth_;
	int attackRange_;
	int moveRange_;
	int speed_;
	bool moving_ = false;
	bool moved_ = false;
	Vector2D<int> boxPosition_;
	Team* team_;
	Box* box_;
public:
	Unit(Texture* texture, Vector2D<int> pos, Vector2D<int> size, int attack, int defense, int maxHealth, int speed, int attackRange, int moveRange)
		: GameObject(texture, pos, size), attack_(attack), defense_(defense), maxHealth_(maxHealth), health_(maxHealth), speed_(speed), attackRange_(attackRange), moveRange_(moveRange) {}
	virtual ~Unit() {};
	virtual int getAttack() const { return attack_; }
	virtual int getDefense() const { return defense_; }
	int getAttackRange() const { return attackRange_; }
	int getMoveRange() const { return moveRange_; }
	int getHealth() const { return health_; }
	virtual int getMaxHealth() const { return maxHealth_; }
	bool getMoving() const { return moving_; }
	bool getMoved() const { return moved_; }
	bool getSpeed() const { return speed_; }
	Team* getTeam() const { return team_; }
	Vector2D<int> getBoxPosition() const { return boxPosition_; }
	void moveTowards(Vector2D<int> pos);
	void setMoving(bool moving);
	void setMoved(bool moved);
	void setBoxPosition(Vector2D<int> position);
	void setTeam(Team* team);
	void moveToBox(Box * box);
	virtual void loseHealth(int healt);
};


// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"
#include "Team.h"
#include "Box.h"
#include "Text.h"

class Team;

class Unit : public GameObject
{
private:
      int attack_;
      int maxHealth_;
      int attackRange_;
      int moveRange_;
      int speed_;
      bool moving_ = false;
      bool moved_ = false;
      Vector2D<int> boxPosition_;
      Team* team_ = nullptr;

protected:
      Box* box_ = nullptr;
      Text* healthText = nullptr;
      int health_;

 public:
    Unit(Texture *texture, Box *box, int attack, int health, int speed, int attackRange, int moveRange);
    virtual ~Unit();
    int getAttack() const { return attack_; }
    int getAttackRange() const { return attackRange_; }
    int getMoveRange() const { return moveRange_; }
      virtual int getMaxHealth() const { return maxHealth_; }
      virtual int getHealth() const { return health_; }
    bool getMoving() const { return moving_; }
    bool getMoved() const { return moved_; }
    bool getSpeed() const { return speed_; }
    Team *getTeam() const { return team_; }
    Box *getBox() const { return box_; }
    Vector2D<int> getBoxPosition() const { return boxPosition_; }
    void moveTowards(Vector2D<int> pos);
    void setMoving(bool moving);
    void setMoved(bool moved);
    void setTeam(Team *team);
      virtual void moveToBox(Box * box);
      virtual void loseHealth(int health);
      virtual void render() const;
};

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Unit.h"

class Battalion : public Unit
{
 private:
    int battalionSize_;
    Text * sizeText_ = nullptr;

    string sizeToString() const;

 public:
    Battalion(Texture* texture, Box * box, int attack, int defense, int health, int speed,
              int attackRange, int moveRange, int prize, int battalionSize);
    virtual ~Battalion();

    int getBattalionSize() const { return battalionSize_; }
    void setBattalionSize(int battalionSize);

    virtual int getAttack() const;
    virtual int getMaxHealth() const;
    virtual int getPrize() const;

    virtual int loseHealth(int attack);

    virtual void moveToBox(Box * box);
    virtual void render() const;
};

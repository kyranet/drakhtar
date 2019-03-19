// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Unit.h"

class Battalion : public Unit
{
 private:
    int battalionSize_;
    Text * sizeText_ = nullptr;

 public:
    Battalion(Texture* texture, Box * box, int attack, int health, int speed,
              int attackRange, int moveRange, int battalionSize);
    virtual ~Battalion();

    int getBattalionSize() const { return battalionSize_; }
    void setBattalionSize(int battalionSize);

    virtual int getAttack() const;
    virtual int getMaxHealth() const;

    virtual void loseHealth(int health);

    virtual void moveToBox(Box * box);
    virtual void render() const;
};

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Battalion.h"
#include "Game.h"


string Battalion::sizeToString() const
{
    return to_string(battalionSize_);
}

Battalion::Battalion(Texture * texture, Box * box, int attack, int defense, int health,
    int speed, int attackRange, int moveRange, int prize, int battalionSize)
    : Unit(texture, box, attack, defense, health, speed, attackRange, moveRange, prize),
      battalionSize_(battalionSize)
{
    health_ = Unit::getMaxHealth() * battalionSize_;

    SDL_Color textColor = { 255, 255, 255, 255 };

    healthText_->setText(healthToString());

    auto rect = box_->getRect();

    sizeText_ =
        new Text(Game::getInstance()->getRenderer(),
            FontManager::get("Retron2000"),
            { rect.x + rect.w / 2 , rect.y + rect.h * 4 / 5 },
            textColor,
            sizeToString(),
            rect.w * 2);
}

Battalion::~Battalion()
{
    if (sizeText_ != nullptr) {
        delete sizeText_;
        sizeText_ = nullptr;
    }
}

void Battalion::setBattalionSize(int battalionSize)
{
    battalionSize_ = battalionSize;
    sizeText_->setText(sizeToString());
}

int Battalion::getAttack() const
{
    return Unit::getAttack() * battalionSize_;
}


int Battalion::getMaxHealth() const
{
    return Unit::getMaxHealth() * battalionSize_;
}

int Battalion::getPrize() const
{
    return Unit::getPrize() * battalionSize_;
}

int Battalion::loseHealth(int attack)
{
    int health = Unit::loseHealth(attack);
    if (Unit::getMaxHealth() <= health) {
        battalionSize_ -= health / Unit::getMaxHealth();
        if (battalionSize_ < 0)
            battalionSize_ = 0;
        sizeText_->setText(sizeToString());
    }
    return health;
}

void Battalion::moveToBox(Box * box)
{
    Unit::moveToBox(box);

    auto rect = box_->getRect();

    sizeText_->setPos(rect.x + rect.w / 2, rect.y + rect.h * 4 / 5);
}

void Battalion::render() const
{
    Unit::render();
    sizeText_->render();
}

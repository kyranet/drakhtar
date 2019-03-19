// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Battalion.h"
#include "Game.h"


Battalion::Battalion(Texture * texture, Box * box, int attack, int health,
                     int speed, int attackRange, int moveRange, int battalionSize)
    : Unit(texture, box, attack, health, speed, attackRange, moveRange),
      battalionSize_(battalionSize)
{
    health_ = Unit::getMaxHealth() * battalionSize_;

    SDL_Color textColor;
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
    textColor.a = 255;
    healthText->setText("Salud: " + to_string(this->getHealth()));

    sizeText_ =
    new Text(Game::getInstance()->getRenderer(), FontManager::get("Retron2000"),
    { box_->getRect().x + box_->getRect().w / 2 , box_->getRect().y + box_->getRect().h * 4 / 5 },
    textColor, "Units: " + to_string(battalionSize_), box_->getRect().w * 2);
}

Battalion::~Battalion()
{
    if (sizeText_ != nullptr) {
        delete sizeText_;
    }
    sizeText_ = nullptr;
}

void Battalion::setBattalionSize(int battalionSize)
{
    battalionSize_ = battalionSize;
    sizeText_->setText("Units: " + to_string(battalionSize_));
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
    sizeText_->setText("Units: " + to_string(battalionSize_));
}

void Battalion::moveToBox(Box * box)
{
    Unit::moveToBox(box);

    sizeText_->setPos(box_->getRect().x + box_->getRect().w / 2, box_->getRect().y + box_->getRect().h * 4 / 5);
}

void Battalion::render() const
{
    Unit::render();
    sizeText_->render();
}

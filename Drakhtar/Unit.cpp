// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Unit.h"
#include "Game.h"


string Unit::healthToString() const
{
    return "Salud: " + to_string(getHealth())
}

Unit::Unit(Texture *texture, Box *box, int attack, int defense, int health, int speed, int attackRange, int moveRange, int prize)
    : GameObject(texture,
        Vector2D<int>(box->getRect().x + box->getRect().w / 2, box->getRect().y + box->getRect().h / 2),
        Vector2D<int>(box->getRect().w * 1.25, box->getRect().h * 1.25)),
    attack_(attack), defense_(defense), health_(health), maxHealth_(health), speed_(speed),
    attackRange_(attackRange), moveRange_(moveRange), box_(box), prize_(prize)
{
    box->setContent(this);
    SDL_Color textColor = { 255, 255, 255, 255 };
    
    auto rect = box_->getRect();

    healthText_ = new Text(Game::getInstance()->getRenderer(),
        FontManager::get("Retron2000"),
        { rect.x + rect.w /2 , rect.y + rect.h/5 },
        textColor,
        healthToString(),
        rect.w*2);
}

Unit::~Unit()
{
    if (healthText_ != nullptr) {
        delete healthText_;
        healthText_ = nullptr;
    }
}

void Unit::moveTowards(Vector2D<int> pos)
{
    // If it's not the unit's turn, cancel any action
    if (!moving_)
        return;

    // TODO(Carlos): Do any logic here, interact with the Board
    // TODO(Carlos): Maybe Unit->Team->Board?
}

void Unit::setMoving(bool moving)
{
    moving_ = moving;
}

void Unit::setMoved(bool moved)
{
    moved_ = moved;
}

void Unit::setTeam(Team *team)
{
    team_ = team;
}

void Unit::moveToBox(Box *newBox)
{
    // If it's not the unit's turn, cancel any action
    // if (!moving_) return;

    box_->setContent(nullptr);
    pos_ = Vector2D<int>(newBox->getRect().x + newBox->getRect().w / 2, newBox->getRect().y + newBox->getRect().h / 2);
    box_ = newBox;
    newBox->setContent(this);

    auto rect = box_->getRect();

    healthText_->setPos(rect.x + rect.w / 2, rect.y + rect.h / 5);
    setMoved(true);
    setMoving(false);
}

int Unit::loseHealth(int attack)
{
    int health = attack - this->getDefense();
    if (health < 0)
        health = 0;
    cout << "Health: " << health_ << " Damage: " << health;
    health_ -= health;
    if(health != 0)
        healthText_->setText(healthToString());
    cout << " Remaining: " << health_ << endl;
    // TODO(Carlos): Send "Unit killed" event if health_ <= 0;
    return health;
}

void Unit::render() const
{
    GameObject::render();
    healthText_->render();
}

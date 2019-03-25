// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Unit.h"
#include "../Managers/FontManager.h"
#include "../Structures/Team.h"
#include "../Utils/Vector2D.h"
#include "Box.h"
#include "Text.h"


Unit::Unit(Scene *scene, Texture *texture, Box *box, int attack, int defense,
    int health, int speed, int attackRange, int moveRange, int prize)
    : GameObject(scene, texture,
                 Vector2D<int>(box->getRect().x + box->getRect().w / 2,
                               box->getRect().y + box->getRect().h / 2),
                 Vector2D<int>(static_cast<int>(box->getRect().w * 1.25),
                               static_cast<int>(box->getRect().h * 1.25))),
    attack_(attack),
    defense_(defense),
    health_(health),
    maxHealth_(health),
    speed_(speed),
    attackRange_(attackRange),
    moveRange_(moveRange),
    box_(box),
    prize_(prize) {
    
    box->setContent(this);
    SDL_Color textColor = { 255, 255, 255, 255 };

    auto rect = box_->getRect();

    healthText_ = new Text(scene,
        FontManager::get("Retron2000"),
        { rect.x + rect.w / 2 , rect.y + rect.h / 6 },
        textColor,
        healthToString(),
        rect.w * 2);
}

Unit::~Unit()
{
    if (healthText_ != nullptr) {
        delete healthText_;
        healthText_ = nullptr;
    }
}


void Unit::setMoving(bool moving) { moving_ = moving; }

void Unit::setMoved(bool moved) { moved_ = moved; }

void Unit::setTeam(Team *team) { team_ = team; }

void Unit::moveToBox(Box *newBox) {
  // If it's not the unit's turn, cancel any action
  // if (!moving_) return;

  box_->setContent(nullptr);
  setPosition(Vector2D<int>(newBox->getRect().x + newBox->getRect().w / 2,
                            newBox->getRect().y + newBox->getRect().h / 2));
  box_ = newBox;
  newBox->setContent(this);
  auto rect = box_->getRect();
  healthText_->setPosition( { rect.x + rect.w / 2,
      rect.y + rect.h / 6 } );
  setMoved(true);
  setMoving(false);

}

int Unit::loseHealth(int attack) {
    int health = attack - this->getDefense();
    if (health < 0)
        health = 1;
    health_ -= health;
    healthText_->setText(healthToString());
    return health;
}

void Unit::render() const {
  GameObject::render();
  healthText_->render();
}

string Unit::healthToString() const
{
    return std::to_string(getHealth()) + " HP";
}

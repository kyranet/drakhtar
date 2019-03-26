// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Unit.h"
#include <string>
#include "../Managers/FontManager.h"
#include "../Structures/Game.h"
#include "../Structures/Team.h"
#include "../Utils/Vector2D.h"
#include "Box.h"
#include "Text.h"

Unit::Unit(Scene *scene, Texture *texture, Box *box, int attack, int health,
           int speed, int attackRange, int moveRange)
    : GameObject(scene, texture,
                 Vector2D<int>(box->getRect().x + box->getRect().w / 2,
                               box->getRect().y + box->getRect().h / 2),
                 Vector2D<int>(static_cast<int>(box->getRect().w * 2),
                               static_cast<int>(box->getRect().h * 2))),
      attack_(attack),
      health_(health),
      maxHealth_(health),
      speed_(speed),
      attackRange_(attackRange),
      moveRange_(moveRange),
      box_(box) {
  box->setContent(this);
  SDL_Color textColor;
  textColor.r = 255;
  textColor.g = 255;
  textColor.b = 255;
  textColor.a = 255;

  healthText_ = new Text(scene_, FontManager::get("Retron2000"),
                         {box_->getRect().x + box_->getRect().w / 2,
                          box_->getRect().y + box_->getRect().h / 5},
                         textColor, "Salud: " + std::to_string(getHealth()),
                         box_->getRect().w * 2);
}

Unit::~Unit() {
  if (healthText_ != nullptr) delete healthText_;
  healthText_ = nullptr;
}

void Unit::moveTowards(Vector2D<int> pos) {
  // If it's not the unit's turn, cancel any action
  if (!moving_) return;

  // TODO(Carlos): Do any logic here, interact with the Board
  // TODO(Carlos): Maybe Unit->Team->Board?
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
  healthText_->setPosition(
      Vector2D<int>(box_->getRect().x + box_->getRect().w / 2,
                    box_->getRect().y + box_->getRect().h / 5));
  setMoved(true);
  setMoving(false);
}

void Unit::loseHealth(int health) {
  std::cout << "Health: " << health_ << " Damage: " << health;
  health_ -= health;
  if (health_ < 0) {
    health_ = 0;
  }
  healthText_->setText("Salud: " + std::to_string(this->getHealth()));
  if (health_ < 0) {
    health_ = 0;
  }
  std::cout << " Remaining: " << health_ << std::endl;
  // TODO(Carlos): Send "Unit killed" event if health_ <= 0;
}

void Unit::render() const {
  GameObject::render();
  healthText_->render();
}

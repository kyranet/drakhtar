// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <vector>
#include "../Skill.h"
#include "../Unit.h"

class Scene;

class Commander : public Unit {
 protected:
  std::vector<Skill*> skills_;

 public:
  Commander(Scene* scene, Texture* texture, Box* box, int attack, int defense,
            int health, int speed, int attackRange, int moveRange, int prize);
  virtual ~Commander();

  std::vector<Skill*> getSkills() const { return skills_; }

  // Lowers skill cooldown on unit turn
  void onSelect() override;
};

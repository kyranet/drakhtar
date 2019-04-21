// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <vector>

#include "../Skill.h"
#include "../Unit.h"

class Scene;
class Box;

class Commander : public Unit {
 protected:
  /**
   * \brief A vector of all the skills the commander can cast.
   */
  std::vector<Skill*> skills_;

  GameObject* commanderIcon_ = nullptr;

 public:
  Commander(Scene* scene, Texture* texture, Box* box, UnitStats commanderStats);
  virtual ~Commander();
  void render() const override;

  /**
   * \return A vector of all the skills the commander can cast.
   */
  std::vector<Skill*> getSkills() const { return skills_; }

  /**
   * \brief Is called every time it's the commander's turn to lower every
   * skill's cooldown timer and duration timer.
   */
  void onSelect() override;

  void moveToBox(Box* box) override;

  void kill() override;
};

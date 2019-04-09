// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <vector>
#include "../Skill.h"
#include "../Unit.h"

class Scene;

class Commander : public Unit {
 protected:
  /**
   * \brief A vector of all the skills the commander can cast.
   */
  std::vector<Skill*> skills_;

 public:
  Commander(Scene* scene, Texture* texture, Box* box, UnitStats commanderStats);
  virtual ~Commander();

  /**
   * \return A vector of all the skills the commander can cast.
   */
  std::vector<Skill*> getSkills() const { return skills_; }

  /**
   * \brief Is called every time it's the commander's turn to lower every
   * skill's cooldown timer and duration timer.
   */
  void onSelect() override;
};

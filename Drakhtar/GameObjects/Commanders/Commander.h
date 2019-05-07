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

  bool unstoppable_ = false;

  GameObject* commanderIcon_ = nullptr;

 public:
  Commander(const std::string & name, Scene* scene, Texture* texture, Box* box,
            UnitStats commanderStats);
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
  void onDeselect() override;

  void moveToBox(Box* box) override;

  void kill() override;

  void attack(Unit* enemy, bool counter) override;

  bool getUnstoppable() const { return unstoppable_; }
  void setUnstoppable(const bool unstoppable) { unstoppable_ = unstoppable; }
};

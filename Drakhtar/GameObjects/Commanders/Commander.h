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
  Commander(const std::string& name, Scene* scene, Texture* texture, Box* box,
            UnitStats commanderStats);
  virtual ~Commander();

  /**
   * \return A vector of all the skills the commander can cast.
   */
  std::vector<Skill*> getSkills() const { return skills_; }

  void moveToBox(Box* box) override;

  void kill() override;

  void setCommanderHealthBar();
};

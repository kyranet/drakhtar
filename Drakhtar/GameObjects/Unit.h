// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <string>

#include "GameObject.h"
#include "Utils/Constants.h"

class Team;
class Box;
class Text;
class HealthBar;
class Scene;

class Unit : public GameObject {
  Team* team_ = nullptr;
  std::string type_;

 protected:
  Box* box_ = nullptr;
  Text* healthText_ = nullptr;
  HealthBar* healthBar_ = nullptr;
  bool isCommander_ = false;

  const UnitStats baseStats_;

 public:
  Unit(Scene* scene, Texture* texture, Box* box, UnitStats stats,
       const std::string& type);
  virtual ~Unit();

  void awake() override;
  bool isCommander() const;

  UnitStats getBaseStats() const { return baseStats_; }
  Team* getTeam() const { return team_; }
  Box* getBox() const { return box_; }
  std::string getType() const { return type_; }

  void setTeam(Team* team) { team_ = team; }

  HealthBar* getHealthBar() const { return healthBar_; }
  virtual void setHealthBar();

  Text* getHealthText() const { return healthText_; }

  virtual void moveToBox(Box* box);
  void update() override;
  virtual void kill();

  virtual void setBuffed(bool buffed);
  virtual void setDebuffed(bool debuffed);

  std::string healthToString() const;
};

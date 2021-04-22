// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"

class Commander;
class GameScene;
class Texture;
class ButtonText;
class Skill;
class ListenerOnHover;
class SkillDescriptionBox;

class SkillButton : public GameObject {
  /**
   * \brief The commander whose skill this button triggers.
   */
  Commander* commander_;

  /**
   * \brief The skill from the commander's skill vector this button triggers.
   */
  Skill* skill_;

  /**
   * \brief The game board, required info for most skills.
   */
  GameScene* gameScene_;

  /**
   * \brief Darkened texture to show when disabled.
   */
  Texture* disabledText_;

  /**
   * \brief The object that contains the text displayed over the button.
   */
  ButtonText* buttonText_;

  ListenerOnHover* hoverListener_;

  SkillDescriptionBox* skillDescriptionBox_;

  bool hovered_ = false;

  int increSize_ = 15;

  bool isActive() const;

 public:
  SkillButton(GameScene* scene, Texture* texture, Texture* disabledText,
              Vector2D<int> pos, Vector2D<int> size, Commander* commander,
              int skill);

  /**
   * \brief Capture events, overrides GameObject's handleEvents.
   * \param e: The event to be processed.
   */
  void handleEvents(SDL_Event e) override;
  void update() override;
  void render(SDL_Rect) const override;

  Skill* getSkill() const { return skill_; }
};

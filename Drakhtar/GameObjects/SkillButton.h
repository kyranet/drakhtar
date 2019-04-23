// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"

class Commander;
class GameScene;

class SkillButton : public GameObject {
  /**
   * \brief The commander whose skill this button triggers.
   */
  Commander* commander_;

  /**
   * \brief The skill from the commander's skill vector this button triggers.
   */
  int skill_;

  /**
   * \brief The game board, required info for most skills.
   */
  GameScene* gameScene_;

 public:
  SkillButton(GameScene* scene, Texture* texture, Vector2D<int> pos,
              Vector2D<int> size, Commander* commander,
              int skill);

  /**
   * \brief Capture events, overrides GameObject's handleEvents.
   * \param The event to be processed.
   */
  void handleEvents(SDL_Event e) override;
};

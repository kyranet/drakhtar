// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Board.h"
#include "Commanders/Commander.h"
#include "GameObject.h"

class SkillButton : public GameObject {
 private:
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
  Board* board_;

 public:
  SkillButton(Scene* scene, Texture* texture, Vector2D<int> pos,
              Vector2D<int> size, Board* board, Commander* commander,
              int skill);

  /**
   * \brief Capture events, overrides GameObject's handleEvents.
   * \param The event to be processed.
   */
  void handleEvents(SDL_Event e) override;
};

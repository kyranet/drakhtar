// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../GameObjects/GameObject.h"
#include "EventListener.h"
#include "SDL.h"
#include "Utils/Vector2D.h"

/**
 * \brief The click listener for game objects. This is an abstract class and
 * must be extended.
 */
class ListenerOnClick : public EventListener {
  /**
   * \brief Whether or not the player is clicking the game object for this
   * instance.
   */
  bool clicked_ = false;

 public:
  /**
   * \brief Creates a ListenerOnClick event listener.
   * \param gameObject The GameObject that listens to this instance.
   */
  explicit ListenerOnClick(GameObject *gameObject)
      : EventListener(gameObject) {}

  /**
   * \brief Runs this event listener with any event and filters them.
   * \param event The event received from SDL's poll.
   */
  void run(SDL_Event event) override;

  /**
   * \brief Runs when this listener has detected a click start to this game
   * object.
   */
  virtual void onClickStart() {}

  /**
   * \brief Runs when this listener has detected a click hold to this game
   * object.
   */
  virtual void onClickStay() {}

  /**
   * \brief Runs when this listener has detected a click stop from this game
   * object.
   */
  virtual void onClickStop() {}
};

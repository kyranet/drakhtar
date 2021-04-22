// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../GameObjects/GameObject.h"
#include "EventListener.h"
#include "SDL.h"
#include "Utils/Vector2D.h"

/**
 * \brief The hover listener for game objects. This is an abstract class and
 * must be extended.
 */
class ListenerOnHover : public EventListener {
 protected:
  /**
   * \brief Whether or not the player is hovering a game object for this
   * instance.
   */
  bool hovered_ = false;

 public:
  /**
   * \brief Creates a ListenerOnHover event listener.
   * \param gameObject The GameObject that listens to this instance.
   */
  explicit ListenerOnHover(GameObject* gameObject)
      : EventListener(gameObject) {}

  /**
   * \brief Runs this event listener with any event and filters them.
   * \param event The event received from SDL's poll.
   */
  void run(SDL_Event event) override;
  /**
   * \brief Runs when this listener has detected a hover start to this game
   * object.
   */
  virtual void onHoverStart() {}

  /**
   * \brief Runs when this listener has detected a hover hold to this game
   * object.
   */
  virtual void onHoverStay() {}

  /**
   * \brief Runs when this listener has detected a hover stop from this game
   * object.
   */
  virtual void onHoverStop() {}
};

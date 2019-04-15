// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "../GameObjects/GameObject.h"

/**
 * \brief The abstract EventListener class, it must be inherited and override
 * EventListener::run(SDL_Event event) before using it.
 */
class EventListener {
  /**
   * \brief The GameObject instance that owns this.
   */
  GameObject* gameObject_;

 public:
  /**
   * \brief Construct a new EventListener.
   * \param gameObject The GameObject instance that owns this listener.
   */
  explicit EventListener(GameObject* gameObject);

  /**
   * \brief Destruct this EventListener.
   */
  virtual ~EventListener() = default;

  /**
   * \brief Processes the events as they are received from the event loop.
   * \param event The SDL event received for further processing.
   */
  virtual void run(SDL_Event event) = 0;

  /**
   * \brief Returns the GameObject instance that owns this listener.
   * \return The GameObject that owns this listener.
   */
  GameObject* getGameObject() const;
};

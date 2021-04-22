// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "SDL.h"

/**
 * \brief The TimePool utility that assists interval-running loops by checking
 * the remaining times between them.
 */
class TimePool {
  /**
   * \brief The amount of milliseconds that need to occur for the next interval
   * to run.
   */
  Uint32 ticksInterval_ = 0;
  /**
   * \brief The amount of milliseconds accumulated since the last run.
   */
  Uint32 ticksAccumulated_ = 0;
  /**
   * \brief The last time in milliseconds this instance received a call to next.
   */
  Uint32 ticksLast_ = 0;

 public:
  /**
   * \brief Create a new instance of TimePool, this instance must get its next
   * method called.
   * \param ticksInterval The amount of milliseconds that need to occur for the
   * next interval to run.
   * \param now The current time in milliseconds.
   */
  TimePool(Uint32 ticksInterval, Uint32 now);
  /**
   * \brief Checks if the interval has already happened. This mutates the
   * instance setting up all its internal properties.
   * \param now The current time in milliseconds
   * \return Whether or not the interval is ready to run.
   */
  bool next(Uint32 now);
  /**
   * \brief Get the remaining time from the last time next() was called to the
   * next interval.
   * \return The remaining time in milliseconds for the next interval.
   */
  Uint32 getRemaining() const;
};

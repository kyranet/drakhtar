// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "DrakhtarError.h"

/**
 * \brief The SDL error class for any operative error related to the SDL2
 * library.
 */
class SDLError final : public DrakhtarError {
 public:
  /**
   * \brief Create a SDL Error instance.
   * \param message The error message description.
   */
  explicit SDLError(const std::string &message)
      : DrakhtarError("[SDL]: " + message) {}
};

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "DrakhtarError.h"

class SDLError final : public DrakhtarError {
 public:
  /**
   * \brief Create a SDL Error instance.
   * \param message The error message description.
   */
  explicit SDLError(const std::string &message)
      : DrakhtarError("[SDL]: " + message) {}
};

// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "DrakhtarError.h"

class TeamedUnitError final : public DrakhtarError {
 public:
  /**
   * \brief Create a Teamed Unit Error instance.
   * \param message The error message description.
   */
  explicit TeamedUnitError(const std::string &message)
      : DrakhtarError(message) {}
};

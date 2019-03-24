// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "DrakhtarError.h"
#include <SDL.h>

class TeamedUnitError : public DrakhtarError
{
 public:
    explicit TeamedUnitError(const string &m) : DrakhtarError(m) {}
};

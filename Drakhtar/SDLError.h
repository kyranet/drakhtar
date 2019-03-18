// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "DrakhtarError.h"
#include <SDL.h>

class SDLError : public DrakhtarError
{
 public:
    explicit SDLError(const string &m) : DrakhtarError("[SDL]: " + m) {}
};

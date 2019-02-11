#pragma once

#include "DrakhtarError.h"
#include <SDL.h>

class SDLError : public DrakhtarError
{
public:
	SDLError(const string &m) : DrakhtarError("[SDL]: " + m) {}
};

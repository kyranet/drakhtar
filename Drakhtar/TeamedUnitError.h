#pragma once

#include "DrakhtarError.h"
#include <SDL.h>

class TeamedUnitError : public DrakhtarError
{
public:
	TeamedUnitError(const string &m) : DrakhtarError(m) {}
};

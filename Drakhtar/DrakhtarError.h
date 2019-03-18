// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include <exception>
#include <stdexcept>
using namespace std;

class DrakhtarError : public logic_error
{
 public:
    explicit DrakhtarError(const string &m) : logic_error("Arkanoid Error " + m) {}
};

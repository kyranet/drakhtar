#pragma once

#include <exception>
#include <stdexcept>
using namespace std;

class DrakhtarError : public logic_error
{
public:
	DrakhtarError(const string &m) : logic_error("Arkanoid Error " + m) {}
};

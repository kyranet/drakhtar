#pragma once
#include <vector>
#include "Unit.h"
using namespace std;

class UnitFactory
{
private:
	vector<Unit*> unitPool;

public:
	UnitFactory();
	~UnitFactory();
};


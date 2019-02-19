#pragma once
#include <vector>
#include "Battalion.h"

using namespace std;

class UnitFactory
{
private:

public:
	UnitFactory() {};
	~UnitFactory();
	Unit * newSoldier(Team * team);
	Unit * newArcher(Team * team);
	Unit * newKnight(Team * team);
	Unit * newWizard(Team * team);
	Unit * newMonster(Team * team);
};


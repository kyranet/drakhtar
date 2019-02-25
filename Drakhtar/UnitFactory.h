#pragma once
#include <vector>
#include "Battalion.h"
#include "Box.h"

using namespace std;

class UnitFactory
{
private:

public:
	UnitFactory() {};
	~UnitFactory();
	Unit * newSoldier(Team * team, Box * box);
	Unit * newArcher(Team * team, Box * box);
	Unit * newKnight(Team * team, Box * box);
	Unit * newWizard(Team * team, Box * box);
	Unit * newMonster(Team * team, Box * box);
};


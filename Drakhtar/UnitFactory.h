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
	Unit * newSoldier(Team * team, Box * box, int size);
	Unit * newArcher(Team * team, Box * box, int size);
	Unit * newKnight(Team * team, Box * box, int size);
	Unit * newWizard(Team * team, Box * box, int size);
	Unit * newMonster(Team * team, Box * box, int size);
};


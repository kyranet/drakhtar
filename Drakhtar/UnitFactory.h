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
	Unit* newSoldier(Team* team, Box* box, int const& size);
	Unit* newArcher(Team* team, Box* box, int const& size);
	Unit* newKnight(Team* team, Box* box, int const& size);
	Unit* newWizard(Team* team, Box* box, int const& size);
	Unit* newMonster(Team* team, Box* box, int const& size);
};

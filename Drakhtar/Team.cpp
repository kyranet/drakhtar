#include "Team.h"
#include "TeamedUnitError.h"

Team::Team(Board* board)
	: board_(board)
{
}

Team::~Team()
{
	board_ = nullptr;
}

void Team::addUnit(Unit* unit)
{
	if (unit->getTeam() != nullptr) {
		throw new TeamedUnitError("This unit already has a team.");
	}
	unit->setTeam(this);

	// Gets the sorted position. If it does not find an unit
	// with lower speed, it gets pushed to the end, otherwise
	// it gets pushed right before the first slower one.
	auto index = findInsertPosition(unit);
	if (index == units_.end()) units_.push_back(unit);
	else units_.insert(index, unit);
}

void Team::removeUnit(Unit* unit)
{
	units_.remove(unit);
}

list<Unit*>::iterator Team::findInsertPosition(Unit* unit)
{
	int i = 0;
	auto it = units_.begin();
	auto end = units_.end();
	while (it != end)
	{
		if (unit->getSpeed() > (*it)->getSpeed()) return it;
		i++;
	}

	return end;
}

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

void Team::addUnit(GameObject* unit)
{
	// TODO: Uncomment this once Unit has merged with
	// team support.
	// if (unit->team != nullptr) {
	// 	throw new TeamedUnitError("This unit already has a team.");
	// }
	// unit->setTeam(this);

	// TODO: Once Unit has been done, find the first
	// slower unit relative to the unit trying to add
	// and insert at that index. This is so units_ do
	// not need to be re-sorted.
	units_.push_back(unit);
}

void Team::removeUnit(GameObject* unit)
{
	units_.remove(unit);
}

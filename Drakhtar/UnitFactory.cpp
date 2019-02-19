#include "UnitFactory.h"




UnitFactory::~UnitFactory()
{
}

Unit * UnitFactory::newSoldier(Team * team)
{
	int soldierAttack = 0;
	int soldierDefense = 0;
	int soldierHealth = 0;
	int soldierAttackRange = 1;
	int soldierMoveRange = 3;
	int soldierSpeed = 0;
	Unit * unit = (Unit*) new Battalion(&Texture(), soldierAttack, soldierDefense, soldierHealth, soldierSpeed, soldierAttackRange, soldierMoveRange, 0);
	unit->setTeam(team);
	return unit;

	
}

Unit * UnitFactory::newArcher(Team * team)
{
	int archerAttack = 0;
	int archerDefense = 0;
	int archerHealth = 0;
	int archerAttackRange = 3;
	int archerMoveRange = 1;
	int archerSpeed = 0;


	Unit * unit = (Unit*) new Battalion(&Texture(), archerAttack, archerDefense, archerHealth, archerSpeed, archerAttackRange, archerMoveRange, 0);
	unit->setTeam(team);
	return unit;
}

Unit * UnitFactory::newKnight(Team * team)
{
	int knightAttack = 0;
	int knightDefense = 0;
	int knightHealth = 0;
	int knightAttackRange = 1;
	int knightMoveRange = 5;
	int knightSpeed = 0;


	Unit * unit = (Unit*) new Battalion(&Texture(), knightAttack, knightDefense, knightHealth, knightSpeed, knightAttackRange, knightMoveRange, 0);
	unit->setTeam(team);
	return unit;
}

Unit * UnitFactory::newWizard(Team * team)
{
	int wizardAttack = 0;
	int wizardDefense = 0;
	int wizardHealth = 0;
	int wizardAttackRange = 2;
	int wizardMoveRange = 1;
	int wizardSpeed = 0;


	Unit * unit = (Unit*) new Battalion(&Texture(), wizardAttack, wizardDefense, wizardHealth, wizardSpeed, wizardAttackRange, wizardMoveRange, 0);
	unit->setTeam(team);
	return unit;
}

Unit * UnitFactory::newMonster(Team * team)
{
	int monsterAttack = 0;
	int monsterDefense = 0;
	int monsterHealth = 0;
	int monsterAttackRange = 1;
	int monsterMoveRange = 5;
	int monsterSpeed = 0;


	Unit * unit = (Unit*) new Battalion(&Texture(), monsterAttack, monsterDefense, monsterHealth, monsterSpeed, monsterAttackRange, monsterMoveRange, 0);
	unit->setTeam(team);
	return unit;
}

#include "UnitFactory.h"




UnitFactory::~UnitFactory()
{
}

Unit * UnitFactory::newSoldier(Team * team, Box * box)
{
	int soldierAttack = 5;
	int soldierDefense = 4;
	int soldierHealth = 10;
	int soldierAttackRange = 1;
	int soldierMoveRange = 3;
	int soldierSpeed = 3;

	Unit * unit = (Unit*) new Battalion(&Texture(), box, soldierAttack, soldierDefense, soldierHealth, soldierSpeed, soldierAttackRange, soldierMoveRange, 0);
	unit->setTeam(team);
	return unit;

	
}

Unit * UnitFactory::newArcher(Team * team, Box * box)
{
	int archerAttack = 6;
	int archerDefense = 2;
	int archerHealth = 10;
	int archerAttackRange = 3;
	int archerMoveRange = 1;
	int archerSpeed = 3;


	Unit * unit = new Battalion(&Texture(), box, archerAttack, archerDefense, archerHealth, archerSpeed, archerAttackRange, archerMoveRange, 0);
	unit->setTeam(team);
	return unit;
}

Unit * UnitFactory::newKnight(Team * team, Box * box)
{
	int knightAttack = 8;
	int knightDefense = 7;
	int knightHealth = 15;
	int knightAttackRange = 1;
	int knightMoveRange = 5;
	int knightSpeed = 5;


	Unit * unit = new Battalion(&Texture(), box, knightAttack, knightDefense, knightHealth, knightSpeed, knightAttackRange, knightMoveRange, 0);
	unit->setTeam(team);
	return unit;
}

Unit * UnitFactory::newWizard(Team * team, Box * box)
{
	int wizardAttack = 4;
	int wizardDefense = 4;
	int wizardHealth = 7;
	int wizardAttackRange = 2;
	int wizardMoveRange = 1;
	int wizardSpeed = 2;


	Unit * unit = new Battalion(&Texture(), box, wizardAttack, wizardDefense, wizardHealth, wizardSpeed, wizardAttackRange, wizardMoveRange, 0);
	unit->setTeam(team);
	return unit;
}

Unit * UnitFactory::newMonster(Team * team, Box * box)
{
	int monsterAttack = 9;
	int monsterDefense = 10;
	int monsterHealth = 15;
	int monsterAttackRange = 1;
	int monsterMoveRange = 5;
	int monsterSpeed = 1;


	Unit * unit =  new Battalion(&Texture(), box, monsterAttack, monsterDefense, monsterHealth, monsterSpeed, monsterAttackRange, monsterMoveRange, 0);
	unit->setTeam(team);
	return unit;
}

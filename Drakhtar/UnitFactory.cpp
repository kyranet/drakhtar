#include "UnitFactory.h"
#include "TextureManager.h"

UnitFactory::~UnitFactory() { }

Unit * UnitFactory::newSoldier(Team * team, Box * box, int size)
{
	int soldierAttack = 5;
	int soldierHealth = 10;
	int soldierAttackRange = 1;
	int soldierMoveRange = 3;
	int soldierSpeed = 3;

	string textureName;

	if (team->getColor() == Color::BLUE)
		textureName = "Units-BlueSoldier";
	else
		textureName = "Units-RedSoldier";

	Unit* unit = (Unit*) new Battalion(TextureManager::get(textureName), box, soldierAttack, soldierHealth, soldierSpeed, soldierAttackRange, soldierMoveRange, size);
	team->addUnit(unit);
	return unit;
}

Unit * UnitFactory::newArcher(Team * team, Box * box, int size)
{
	int archerAttack = 6;
	int archerHealth = 10;
	int archerAttackRange = 3;
	int archerMoveRange = 1;
	int archerSpeed = 3;

	string textureName;

	if (team->getColor() == Color::BLUE)
		textureName = "Units-BlueArcher";
	else
		textureName = "Units-RedArcher";

	Unit * unit = new Battalion(TextureManager::get(textureName), box, archerAttack, archerHealth, archerSpeed, archerAttackRange, archerMoveRange, size);
	team->addUnit(unit);
	return unit;
}

Unit * UnitFactory::newKnight(Team * team, Box * box, int size)
{
	int knightAttack = 8;
	int knightHealth = 15;
	int knightAttackRange = 1;
	int knightMoveRange = 5;
	int knightSpeed = 5;

	string textureName;

	if (team->getColor() == Color::BLUE)
		textureName = "Units-BlueKnight";
	else
		textureName = "Units-RedKnight";

	Unit * unit = new Battalion(TextureManager::get(textureName), box, knightAttack, knightHealth, knightSpeed, knightAttackRange, knightMoveRange, size);
	team->addUnit(unit);
	return unit;
}

Unit * UnitFactory::newWizard(Team * team, Box * box, int size)
{
	int wizardAttack = 4;
	int wizardHealth = 7;
	int wizardAttackRange = 2;
	int wizardMoveRange = 1;
	int wizardSpeed = 2;

	Unit * unit = new Battalion(TextureManager::get("Units-BlueMage"), box, wizardAttack, wizardHealth, wizardSpeed, wizardAttackRange, wizardMoveRange, size);
	team->addUnit(unit);
	return unit;
}

Unit * UnitFactory::newMonster(Team * team, Box * box, int size)
{
	int monsterAttack = 9;
	int monsterHealth = 15;
	int monsterAttackRange = 1;
	int monsterMoveRange = 5;
	int monsterSpeed = 1;

	string textureName;

	if (team->getColor() == Color::BLUE)
		textureName = "Units-BlueMonster";
	else
		textureName = "Units-RedMonster";

	Unit * unit =  new Battalion(TextureManager::get(textureName), box, monsterAttack, monsterHealth, monsterSpeed, monsterAttackRange, monsterMoveRange, size);
	team->addUnit(unit);
	return unit;
}

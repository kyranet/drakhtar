#include "UnitFactory.h"
#include "TextureManager.h"

UnitFactory::~UnitFactory() { }

Unit* UnitFactory::newSoldier(Team* team, Box* box, int const& size)
{
	int soldierAttack = 5;
	int soldierHealth = 10;
	int soldierAttackRange = 1;
	int soldierMoveRange = 3;
	int soldierSpeed = 3;

	string textureName = team->getColor() == Color::BLUE
		? "Units-BlueSoldier"
		: "Units-RedSoldier";

	auto unit = new Battalion(TextureManager::get(textureName), box, soldierAttack, soldierHealth, soldierSpeed, soldierAttackRange, soldierMoveRange, size);
	team->addUnit(unit);
	return unit;
}

Unit* UnitFactory::newArcher(Team* team, Box* box, int const& size)
{
	int archerAttack = 6;
	int archerHealth = 10;
	int archerAttackRange = 3;
	int archerMoveRange = 1;
	int archerSpeed = 3;

	string textureName = team->getColor() == Color::BLUE
		? "Units-BlueArcher"
		: "Units-RedArcher";

	auto unit = new Battalion(TextureManager::get(textureName), box, archerAttack, archerHealth, archerSpeed, archerAttackRange, archerMoveRange, size);
	team->addUnit(unit);
	return unit;
}

Unit* UnitFactory::newKnight(Team* team, Box* box, int const& size)
{
	int knightAttack = 8;
	int knightHealth = 15;
	int knightAttackRange = 1;
	int knightMoveRange = 5;
	int knightSpeed = 5;

	string textureName = team->getColor() == Color::BLUE
		? "Units-BlueKnight"
		: "Units-RedKnight";

	auto unit = new Battalion(TextureManager::get(textureName), box, knightAttack, knightHealth, knightSpeed, knightAttackRange, knightMoveRange, size);
	team->addUnit(unit);
	return unit;
}

Unit* UnitFactory::newWizard(Team* team, Box* box, int const& size)
{
	int wizardAttack = 4;
	int wizardHealth = 7;
	int wizardAttackRange = 2;
	int wizardMoveRange = 1;
	int wizardSpeed = 2;

	string textureName = team->getColor() == Color::BLUE
		? "Units-BlueMage"
		: "Units-RedMage";

	auto unit = new Battalion(TextureManager::get(textureName), box, wizardAttack, wizardHealth, wizardSpeed, wizardAttackRange, wizardMoveRange, size);
	team->addUnit(unit);
	return unit;
}

Unit* UnitFactory::newMonster(Team* team, Box* box, int const& size)
{
	int monsterAttack = 9;
	int monsterHealth = 15;
	int monsterAttackRange = 1;
	int monsterMoveRange = 5;
	int monsterSpeed = 1;

	string textureName = team->getColor() == Color::BLUE
		? "Units-BlueMonster"
		: "Units-RedMonster";

	auto unit =  new Battalion(TextureManager::get(textureName), box, monsterAttack, monsterHealth, monsterSpeed, monsterAttackRange, monsterMoveRange, size);
	team->addUnit(unit);
	return unit;
}

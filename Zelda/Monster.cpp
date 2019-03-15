#include "pch.h"
#include "Monster.h"

Monster::Monster()
{
	name = nullptr;
	is_Alive = true;
	killing_weapon = nullptr;
}



Monster::~Monster()
{
	if (name)
		delete[] name;
}



Monster::Monster(char const* monster_Name, Item* weapon)
{
	name = new char[strlen(monster_Name) + 1];
	strcpy_s(name, strlen(monster_Name) + 1, monster_Name);

	is_Alive = true;
	killing_weapon = weapon;
}



Item* Monster::getKillingWeapon()
{
	return killing_weapon;
}



void Monster::setKillingWeapon(Item* item)
{
	killing_weapon = item;
}



bool Monster::getLivingState()
{
	return is_Alive;
}



void Monster::setLivingState(bool currentState)
{
	is_Alive = currentState;
}



char* Monster::getMonsterName()
{
	return name;
}
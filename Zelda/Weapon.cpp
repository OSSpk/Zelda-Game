#include "pch.h"
#include "Weapon.h"

Weapon::Weapon()
{

}



Weapon::~Weapon()
{

}



Weapon::Weapon(char const* weapon_Name)
{
	name = new char[strlen(weapon_Name) + 1];
	strcpy_s(name, strlen(weapon_Name) + 1, weapon_Name);
}



int Weapon::getWorth()
{
	return 0;
}
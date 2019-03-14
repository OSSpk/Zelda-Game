#include "pch.h"
#include "Treasure.h"

Treasure::Treasure()
{
	worth = 0;
}



Treasure::~Treasure()
{

}



Treasure::Treasure(char const* treasure_Name, int treasure_Worth)
{
	name = new char[strlen(treasure_Name) + 1];
	strcpy_s(name, strlen(treasure_Name) + 1, treasure_Name);

	worth = treasure_Worth;
}



int Treasure::getWorth()
{
	return worth;
}
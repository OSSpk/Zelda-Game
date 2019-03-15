#include "pch.h"
#include "Item.h"

Item::Item()
{
	name = nullptr;
}



Item::~Item()
{
	if (name)
		delete[] name;
}



char* Item::getItemName()
{
	return name;
}
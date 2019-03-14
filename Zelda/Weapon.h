#pragma once

#include "Item.h"

class Weapon : public Item
{
private:

public:

	Weapon();
	~Weapon();
	Weapon(char const*);

	int getWorth();

};
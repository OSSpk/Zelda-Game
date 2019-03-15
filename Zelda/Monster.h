#pragma once

#include <string.h>

#include "Item.h"

class Monster
{
private:
	char* name;
	bool  is_Alive;
	Item* killing_weapon;


public:

	Monster();
	~Monster();
	Monster(char const*, Item*);

	Item* 	getKillingWeapon();
	void	setKillingWeapon(Item*);
	bool	getLivingState();
	void	setLivingState(bool);
	char*	getMonsterName();

};
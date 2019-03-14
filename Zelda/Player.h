#pragma once

#include "Item.h"
#include "Princess.h"
#include "Room.h"

#include <iostream>

using namespace std;

class Player
{

private:
	char* 		name;
	Princess* 	princess_Pointer;
	Item* 		bag[10];
	Room* 		current_Room;

	bool is_Alive;
	int  cash;

	//Utility Functions

	bool isBagEmpty();
	bool isBagFull();

public:

	Player();
	~Player();
	Player(char const*, Room*);

	bool 	getCurrentState();
	void 	setCurrentState(bool);

	Princess* getPrincess_Pointer();

	void 			CashUpdater();
	int  	getCash();
	char*	getPlayerName();

	bool			Move(char const*, bool&);
	void			Pick(char const*);
	void			Drop(char const*);
	void			Look();
	bool			Attack(char const*);
	void			Exit();


};
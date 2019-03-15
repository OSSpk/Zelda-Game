#pragma once

#include "Room.h"

#include <iostream>
#include <fstream>

using namespace std;

class Castle
{
private:
	static int const numRooms = 9;
	Room rooms[numRooms];

public:
	Room* getRoom(int);

	void LinkRoomsWithOtherThings(Item**, Monster**, Princess*);
	void HiddenRoomsUnlocker(char const*, Monster**);
	void LinkRoom5and8();
	void LinkRoom6and9();

	void setDescriptionOfRooms();
	void setNumbersofRooms();
};
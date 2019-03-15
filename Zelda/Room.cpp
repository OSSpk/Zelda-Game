#include "pch.h"
#include "Room.h"

Room::Room()
{
	for (int i = 0; i < numPaths; ++i)
	{
		paths[i] = nullptr;
	}

	for (int i = 0; i < numItems; ++i)
	{
		items_Present[i] = nullptr;
	}

	monster_Present = nullptr;
	princess_Present = nullptr;

	description = nullptr;
	roomNumber = 0;
}



Room::~Room()
{
	if (description) {
		delete[] description;
	}
}



int Room::directionIndex(char const* direction)
{
	char temp[10];
	strncpy_s(temp, direction, min(sizeof(temp) - 1, strlen(direction)));
	temp[sizeof(temp) - 1] = '\0';
	HelperFunctions::charactersCase(temp);
	if (strcmp(temp, "NORTH") == 0) {
		return 0;
	}

	if (strcmp(temp, "SOUTH") == 0) {
		return 1;
	}

	if (strcmp(temp, "EAST") == 0) {
		return 2;
	}

	if (strcmp(temp, "WEST") == 0) {
		return 3;
	}

	return -1;
}



char const* Room::directionName(int const i)
{
	if (i == 0) {
		return "North";
	}
	if (i == 1) {
		return "South";
	}
	if (i == 2) {
		return "East";
	}
	if (i == 3) {
		return "West";
	}
	return "";
}



bool Room::isRoomFull()
{
	for (int i = 0; i < numItems; ++i) {
		if (items_Present[i] == nullptr) {
			return false;
		}
	}
	return true;
}



//Getters



Room** Room::getPaths()
{
	return paths;
}



Item** Room::getItemsPresent()
{
	return items_Present;
}



Monster* Room::getMonsterPresent()
{
	return monster_Present;
}



Princess* Room::getPrincessPresent()
{
	return princess_Present;
}



char* Room::getDescription()
{
	return description;
}



int Room::getRoomNumber()
{
	return roomNumber;
}




// paths[0] = North
// paths[1] = South
// paths[2] = East
// paths[3] = West



void Room::setNorth(Room* roomNo)
{
	paths[0] = roomNo;
}



void Room::setSouth(Room* roomNo)
{
	paths[1] = roomNo;
}



void Room::setEast(Room* roomNo)
{
	paths[2] = roomNo;
}



void Room::setWest(Room* roomNo)
{
	paths[3] = roomNo;
}



void Room::setItemsPresent(int const itemNo, Item* item)
{
	if (itemNo >= 0 && itemNo < numItems) {
		items_Present[itemNo] = item;
	}
}



void Room::setMonsterPresent(Monster* monster)
{
	monster_Present = monster;
}



void Room::setPrincessPresent(Princess* princess)
{
	princess_Present = princess;
}



void Room::setDesription(char const* room_Description)
{
	description = new char[strlen(room_Description) + 1];
	strcpy_s(description, strlen(room_Description) + 1, room_Description);
}



void Room::setRoomNumber(int const roomNo)
{
	roomNumber = roomNo;
}
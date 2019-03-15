#include "pch.h"
#include "Castle.h"

Room* Castle::getRoom(int const room_No)
{
	if (room_No <= numRooms && room_No > 0) {
		return &rooms[room_No - 1];
	}
	return nullptr;
}



void Castle::LinkRoomsWithOtherThings(Item** items, Monster** monsters, Princess* princess)
{
	//Room1
	rooms[0].setSouth(&rooms[3]);
	rooms[0].setEast(&rooms[1]);
	//room1.west = Exit from castle


	//Room2
	rooms[1].setWest(&rooms[0]);
	rooms[1].setEast(&rooms[2]);
	rooms[1].setSouth(&rooms[4]);

	if (items) {
		rooms[1].setItemsPresent(0, items[0]);
	}


	//Room3
	rooms[2].setWest(&rooms[1]);
	if (items) {
		rooms[2].setItemsPresent(0, items[3]);
	}


	//Room4
	rooms[3].setNorth(&rooms[0]);
	if (items) {
		rooms[3].setItemsPresent(0, items[1]);
	}


	//Room5
	rooms[4].setNorth(&rooms[1]);
	rooms[4].setEast(&rooms[5]);

	if (monsters) {
		rooms[4].setMonsterPresent(monsters[0]);
	}


	//Room6
	rooms[5].setWest(&rooms[4]);

	if (monsters) {
		rooms[5].setMonsterPresent(monsters[1]);
	}


	//Room7
	rooms[6].setEast(&rooms[7]);
	if (items) {
		rooms[6].setItemsPresent(0, items[4]);
	}


	//Room8
	rooms[7].setWest(&rooms[6]);
	rooms[7].setNorth(&rooms[4]);
	if (items) {
		rooms[7].setItemsPresent(0, items[2]);
	}


	//Room9
	rooms[8].setNorth(&rooms[5]);
	if (princess) {
		rooms[8].setPrincessPresent(princess);
	}
}



void Castle::LinkRoom5and8()
{
	rooms[4].setSouth(&rooms[7]);
	rooms[7].setNorth(&rooms[4]);
}



void Castle::LinkRoom6and9()
{
	rooms[5].setSouth(&rooms[8]);
	rooms[8].setNorth(&rooms[5]);
}



void Castle::HiddenRoomsUnlocker(char const* monsterName, Monster** monsters)
{
	if (strcmp(monsterName, (monsters[0]->getMonsterName())) == 0)
	{
		LinkRoom5and8();
	}

	else if (strcmp(monsterName, (monsters[1]->getMonsterName())) == 0)
	{
		LinkRoom6and9();
	}
}



void Castle::setDescriptionOfRooms()
{
	ifstream InputStream("Rooms.txt");
	if (InputStream.is_open())
	{
		char buffer[300];

		for (int i = 0; i < numRooms && !InputStream.eof(); ++i)
		{
			InputStream.getline(buffer, 300);
			rooms[i].setDesription(buffer);
		}
	}
	else {
		cout << "Could not open file";
	}
	InputStream.close();
}



void Castle::setNumbersofRooms()
{
	for (int i = 0; i < numRooms; ++i)
	{
		rooms[i].setRoomNumber(i + 1);
	}
}
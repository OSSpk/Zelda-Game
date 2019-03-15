#pragma once

#include "HelperFunctions.h"
#include "Item.h"
#include "Monster.h"
#include "Princess.h"

class Room
{
private:
	static int const numPaths = 4;
	static int const numItems = 5;

	Room* 		paths[numPaths];
	Item* 		items_Present[numItems];
	Monster*    monster_Present;
	Princess*   princess_Present;

	char*		description;
	int 		roomNumber;


public:
	Room();
	~Room();

	Room** 		getPaths();
	Item**		getItemsPresent();
	Monster*		getMonsterPresent();
	Princess*	getPrincessPresent();
	char*		getDescription();
	int 			getRoomNumber();

	bool				isRoomFull();


	int					directionIndex(char const*);
	char const* 		directionName(int);

	void			setEast(Room*);
	void			setWest(Room*);
	void			setSouth(Room*);
	void			setNorth(Room*);

	void			setMonsterPresent(Monster*);
	void			setItemsPresent(int, Item*);
	void			setPrincessPresent(Princess*);
	void			setDesription(char const*);
	void			setRoomNumber(int);


};
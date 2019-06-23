#include "pch.h"
#include "Zelda.h"

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

using namespace std;

/*Some COLOR Constants*/
const int RED = 12;
const int PURPLE = 13;
const int GREEN = 10;
const int AQUA = 11;
const int YELLOW = 14;
const int WHITE = 15;
const int BLUE = 9;


//---------------------Helper Functions------------------------



void HelperFunctions::charactersCase(char* input)
{
	for (int i = 0; input[i]!='\0'; ++i)
	{
		if(input[i] >= 'a' && input[i] <= 'z')
		{
			input[i] = input[i] - 32;
		}
	}
}



void HelperFunctions::color(int k)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}



//---------------------Item------------------------


Item::Item()
{
	name = nullptr;
}



Item::~Item()
{
	if(name)
		delete[] name;
}



char* Item::getItemName()
{
	return name;
}



//---------------------Treasure------------------------



Treasure::Treasure()
{
	worth = 0;
}



Treasure::~Treasure()
{

}



Treasure::Treasure(char const* treasure_Name , int treasure_Worth)
{
	name = new char [strlen (treasure_Name) + 1];
	strcpy_s(name,strlen (treasure_Name) + 1, treasure_Name);

	worth = treasure_Worth;
}



int Treasure::getWorth()
{
	return worth;
}



//---------------------Weapon------------------------



Weapon::Weapon()
{

}



Weapon::~Weapon()
{

}



Weapon::Weapon(char const* weapon_Name)
{
	name = new char [strlen (weapon_Name) + 1];
	strcpy_s (name, strlen (weapon_Name) + 1, weapon_Name);
}



int Weapon::getWorth()
{
	return 0;
}



//---------------------Monster------------------------



Monster::Monster()
{
	name = nullptr;
	is_Alive = true;
	killing_weapon = nullptr;
}



Monster::~Monster()
{
	if(name)
		delete[] name;
}



Monster::Monster(char const* monster_Name, Item* weapon)
{
	name = new char [strlen(monster_Name) + 1];
	strcpy_s (name,strlen (monster_Name) + 1, monster_Name);

	is_Alive = true;
	killing_weapon = weapon;
}



Item* Monster::getKillingWeapon()
{
	return killing_weapon;
}



void Monster::setKillingWeapon(Item* item)
{
	killing_weapon = item;
}



bool Monster::getLivingState()
{
	return is_Alive;
}



void Monster::setLivingState(bool currentState)
{
	is_Alive = currentState;
}



char* Monster::getMonsterName()
{
	return name;
}



//---------------------Princess------------------------



Princess::Princess()
{
	is_Alive = true;
}



Princess::~Princess()
{

}



bool Princess::getLivingState()
{
	return is_Alive;
}



void Princess::setLivingState(bool currentState)
{
	is_Alive = currentState;
}



//---------------------Room------------------------



Room::Room()
{
	for (int i = 0; i < 4; ++i)
	{
		paths[i] = nullptr;
	}

	for (int i = 0; i < 5; ++i)
	{
		items_Present[i] = nullptr;
	}

	monster_Present  = nullptr;
	princess_Present = nullptr;

	description 	 = nullptr;
	roomNumber 		 = 0;
}



Room::~Room()
{
	if(description)
		delete[] description;
}



int Room::directionIndex(char const* direction)
{
	int i = 0;
	if(strcmp(direction , "NORTH") == 0)
		i = 0;

	else if(strcmp (direction, "SOUTH") == 0)
		i = 1;

	else if(strcmp (direction, "EAST") == 0)
		i = 2;

	else if(strcmp (direction, "WEST") == 0)
		i = 3;

	return i;
}



char* Room::directionName(int i)
{
	char* buffer = new char [10];

	if( i == 0)
		strcpy_s(buffer,10, "North");

	else if(i == 1)
		strcpy_s(buffer,10, "South");

	else if(i == 2)
		strcpy_s(buffer,10, "East");

	else if(i == 3)
		strcpy_s(buffer,10, "West");

	return buffer;
}



bool Room::isRoomFull()
{
	for (int i = 0; i < 5; ++i)
	{
		if (items_Present[i] == nullptr)
		{
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



void Room::setItemsPresent(int itemNo , Item* item)
{
	items_Present[itemNo] = item;
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
	description = new char [strlen(room_Description)+1];
	strcpy_s(description,strlen(room_Description)+1,room_Description);
}



void Room::setRoomNumber(int roomNo)
{
	roomNumber = roomNo;
}



//---------------------Castle------------------------



Castle::Castle()
{

}



Room* Castle::getRoom( int room_No )
{
	return &rooms[room_No - 1];
}



void Castle::LinkRoomsWithOtherThings(Item** items , Monster** monsters , Princess* princess)
{
	//Room1
	rooms[0].setSouth(&rooms[3]);
	rooms[0].setEast(&rooms[1]);
	//room1.west = Exit from castle


	//Room2
	rooms[1].setWest(&rooms[0]);
	rooms[1].setEast(&rooms[2]);
	rooms[1].setSouth(&rooms[4]);

	rooms[1].setItemsPresent(0 , items[0]);


	//Room3
	rooms[2].setWest(&rooms[1]);
	rooms[2].setItemsPresent(0 , items[3]);


	//Room4
	rooms[3].setNorth(&rooms[0]);
	rooms[3].setItemsPresent(0 , items[1]);


	//Room5
	rooms[4].setNorth(&rooms[1]);
	rooms[4].setEast(&rooms[5]);

	rooms[4].setMonsterPresent( monsters[0] );


	//Room6
	rooms[5].setWest(&rooms[4]);

	rooms[5].setMonsterPresent( monsters[1] );


	//Room7
	rooms[6].setEast(&rooms[7]);
	rooms[6].setItemsPresent(0 , items[4]);


	//Room8
	rooms[7].setWest(&rooms[6]);
	rooms[7].setNorth(&rooms[4]);

	rooms[7].setItemsPresent(0 , items[2]);


	//Room9
	rooms[8].setNorth(&rooms[5]);
	rooms[8].setPrincessPresent(princess);
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



void Castle::HiddenRoomsUnlocker(char const* monsterName , Monster** monsters)
{
	if (strcmp(monsterName , (monsters[0]->getMonsterName())) == 0)
	{
		LinkRoom5and8();
	}

	else if (strcmp(monsterName , (monsters[1]->getMonsterName())) == 0)
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

		for (int i = 0; i < 9 && !InputStream.eof(); ++i)
		{
			InputStream.getline(buffer,300);
			rooms[i].setDesription(buffer);
		}
	}
	else
		cout << "Could not open file";
	InputStream.close();
}



void Castle::setNumbersofRooms()
{
	for (int i = 0; i < 9; ++i)
	{
		rooms[i].setRoomNumber(i+1);
	}
}



Castle::~Castle()
{

}



//-------------------Player---------------------



Player::Player(char const* player_Name , Room* room1 )
{
	name = new char [strlen(player_Name) + 1];
	strcpy_s (name,strlen(player_Name) + 1, player_Name);

	current_Room = room1;
	princess_Pointer = nullptr;
	is_Alive = true;
	cash = 0;

	for (int i = 0; i < 10; ++i)
	{
		bag[i] = nullptr;
	}
}



Player::Player()
{

}



Player::~Player()
{
	if (name)
	{
		delete[] name;
	}
}



bool Player::getCurrentState()
{
	return is_Alive;
}



void Player::setCurrentState(bool currentState)
{
	is_Alive = currentState;
}



Princess* Player::getPrincess_Pointer()
{
	return princess_Pointer;
}



char* Player::getPlayerName()
{
	return name;
}



void Player::CashUpdater()
{
	cash = 0;

	for (int i = 0; i < 10; ++i)
	{
		if(bag[i])
		{
			cash = cash + bag[i]->getWorth();
		}
	}
}



int Player::getCash()
{
	return cash;
}



bool Player::isBagEmpty()
{
	for (int i = 0; i < 10; ++i)
	{
		if(bag[i] != nullptr)
			return false;
	}

	return true;
}



bool Player::isBagFull()
{
	bool bag_Full = true;

	for (int i = 0; i < 10 && bag_Full; ++i)
	{
		if(bag[i] == nullptr)
			bag_Full = false;
	}

	return bag_Full;
}



bool Player::Move(char const* direction , bool& exit_Castle)
{
	bool moveSuccessful = false;
	int i = 0;

	i = current_Room->directionIndex(direction);

	if ((i == 3) && ((current_Room->getRoomNumber()) == 1))
	{
		exit_Castle = true;
	}

	else if((current_Room->getPaths())[i] != nullptr)
	{
		current_Room   = (current_Room->getPaths())[i];
		moveSuccessful = true;

		if(current_Room->getPrincessPresent())
		{
			HelperFunctions::color(AQUA);
			cout << "The Princess is standing , waiting for you in the dark . ";
			princess_Pointer= current_Room->getPrincessPresent();
			current_Room->setPrincessPresent(nullptr);
		}

		HelperFunctions::color(RED);
		cout << "\nYou have successfully been moved to Room : " << current_Room->getRoomNumber();
	}

	else
	{
		HelperFunctions::color(RED);
		cout << "\nMOVE " << direction <<" is an invalid command.";
	}

	return moveSuccessful;
}







void Player::Pick(char const* itemName)
{
	bool picked = false;
	bool itemFound = false;

	for (int i = 0; i < 5; ++i)
	{
		if((current_Room->getItemsPresent())[i] != nullptr)
		{
			if(	strcmp((((current_Room->getItemsPresent())[i])->getItemName()) , itemName) == 0)
			{
				itemFound = true;

				if (!isBagFull())
				{
					int j = 0;

					for (; bag[j] != nullptr; ++j)
					{

					}

					bag[j] =  (current_Room->getItemsPresent())[i];
					current_Room->setItemsPresent(i , nullptr);

					picked = true;

					CashUpdater();
				}
				else
					cout << "\nSorry , your bag is already full.";
			}
		}
	}

	HelperFunctions::color(RED);
	if(picked)
		cout <<endl << itemName << " has successfully been picked.";

	else if(itemFound == false)
		cout <<endl << itemName <<" is not present in this room.";
}




void Player::Drop(char const* itemName)
{
	bool dropped = false;
	bool item_in_bag = false;

	for (int i = 0; i < 10; ++i)
	{
		if(bag[i] != NULL)
		{
			if(	strcmp((bag[i])->getItemName() , itemName) == 0)
			{
				item_in_bag = true;

				if(!(current_Room-> isRoomFull()))
				{
					int j = 0;

					for (; (current_Room->getItemsPresent())[j] != nullptr; ++j)
					{

					}

					current_Room->setItemsPresent(j , bag[i]);
					bag[i] = nullptr;

					dropped = true;

					CashUpdater();
				}
				else
				{
					HelperFunctions::color(AQUA);
					cout << "/n/The item" << itemName << " couldn't be dropped as Room "<<current_Room->getRoomNumber()
						 << " is already full.";
				}
			}
		}
	}

	HelperFunctions::color(YELLOW);

	if(dropped)
		cout << endl<< itemName <<" has successfully been dropped.";

	else if(item_in_bag == false)
		cout << endl << itemName <<" couldn't be dropped as it is not present in your bag.";
}





bool Player::Attack(char const* monsterName)
{
	bool killed = false;

	if(current_Room->getMonsterPresent() != nullptr)
	{
		if(((current_Room->getMonsterPresent())->getLivingState()) == true)
		{
			for (int i = 0; i < 10; ++i)
			{
				if( (current_Room->getMonsterPresent())->getKillingWeapon() == bag[i] )
				{
						(current_Room->getMonsterPresent())->setLivingState(false);
						HelperFunctions::color(RED);
						cout << monsterName <<" has been killed . ";

						killed = true;
				}
			}

			if (killed == false)
			{
				setCurrentState(false);
				HelperFunctions::color(RED);
				cout << "/nYour bag doesn't contain the Weapon required to kill " << monsterName;
			}
		}

		else if ((((current_Room->getMonsterPresent())->getLivingState()) == false))
			cout << endl << monsterName << " is already dead.";

	}

	else
		cout << endl << monsterName <<" is not present in this room.";

	return killed;
}



void Player::Look()
{
	HelperFunctions::color(RED);
	cout << "\nCurrently you are in Room "<<current_Room->getRoomNumber()<<". ";
	cout << current_Room->getDescription();

	for (int i = 0; i < 4; ++i)
	{
		HelperFunctions::color(AQUA);
		if ((current_Room->getPaths())[i] != NULL)
			cout << " There is a room to your " << current_Room->directionName(i)<<" .";
	}

	for (int i = 0; i < 5; ++i)
	{
		HelperFunctions::color(WHITE);
		if ((current_Room->getItemsPresent())[i] != NULL)
			cout << " The " << ((current_Room->getItemsPresent())[i])->getItemName() << " is lying on the floor .";
	}

	if(current_Room->getMonsterPresent() != NULL)
	{
		HelperFunctions::color(RED);
		if((current_Room->getMonsterPresent())->getLivingState() == true)
			cout << (current_Room->getMonsterPresent())->getMonsterName()  << " is waiting to kill you beside a locked door.";
		else
			cout << (current_Room->getMonsterPresent())->getMonsterName()  << " is lying dead on the floor.";
	}

	HelperFunctions::color(PURPLE);
	if(princess_Pointer)
		cout << " You have Princess along with you .";

	HelperFunctions::color(GREEN);
	cout << "\nYour bag contains the following items : ";


	if(!isBagEmpty())
	{
		for (int i = 0; i < 10; ++i)
		{
			if (bag[i])
				cout << endl << bag[i] -> getItemName();
		}
	}
	else
		cout << "\nCurrently, your bag is empty.";

	HelperFunctions::color(BLUE);
	cout <<"\nCurrent Cash is : " << getCash();
}



void Player::Exit()
{
	HelperFunctions::color(WHITE);
	cout << "Thankyou " << getPlayerName() <<" for playing Zelda.\nThe game is now exiting .........";
}



//--------------------------Game------------------------------------------



Game::Game()
{
	//Creating Items for the Game
	itemsPtr[0] = new Treasure ("GOLDEN EGG" 	, 500000);
	itemsPtr[1] = new Treasure ("GOLDEN CHALICE" , 500000);
	itemsPtr[2] = new Treasure ("PROOF" , 1000000);
	itemsPtr[3] = new Weapon   ("SHIELD");
	itemsPtr[4] = new Weapon   ("DAGGER");


	//Creating Monsters for the Game
	monstersPtr[0] = new Monster  ("MEDUSA"  ,  itemsPtr[3]);
	monstersPtr[1] = new Monster  ("DRACULA" ,  itemsPtr[4]);


	//Creating Princess for the Game
	princessPtr = new Princess;


	//Creating Castle for the Game
	castlePtr = new Castle;


	//Placing items and monsters in rooms and linking them
	castlePtr->LinkRoomsWithOtherThings(itemsPtr , monstersPtr , princessPtr);
	castlePtr->setDescriptionOfRooms();
	castlePtr->setNumbersofRooms();

	//Code to get the name of the Player
	char username[20];
	HelperFunctions::color(YELLOW);
	cout << "Enter your name : ";
	cin.getline(username , 20);


	//Creating Player for the Game
	playerPtr = new Player (username , castlePtr->getRoom(1));
}



Game::~Game()
{
	for (int i = 0; i < 5; ++i)
	{
		delete itemsPtr[i];
	}


	for (int i = 0; i < 2; ++i)
	{
		delete monstersPtr[i];
	}


	delete princessPtr;

	delete castlePtr;

	delete playerPtr;
}



void Game::displayStory()
{
	ifstream InputStream("Start.txt");
	if (InputStream.is_open())
	{
		HelperFunctions::color(PURPLE);
		char buffer[200];

			while(!InputStream.eof())
			{

				InputStream.getline(buffer,200);
				cout << buffer << endl;
			}
	}
	else
		cout << "Could not open file";
	InputStream.close();
}



void Game::PlayerDead()
{
	ifstream InputStream("EndDead.txt");
	if (InputStream.is_open())
	{
		HelperFunctions::color(RED);

		while(!InputStream.eof())
		{
			char buffer[200];

			while(!InputStream.eof())
			{

				InputStream.getline(buffer,200);
				cout << buffer << endl;
			}
		}
	}
	else
		cout << "Could not open file";
	InputStream.close();
}



void Game::gameCheck()
{
	if(playerPtr->getPrincess_Pointer())
	{
		ifstream InputStream("EndWin.txt");
		if (InputStream.is_open())
		{
			HelperFunctions::color (AQUA);

			char buffer[200];

			while(!InputStream.eof())
			{
				InputStream.getline(buffer,200);
				cout << buffer << endl;
			}
		}
		else
			cout << "Could not open file";
		InputStream.close();
	}



	else
	{

		ifstream InputStream("EndLose.txt");
		if (InputStream.is_open())
		{
			char buffer[200];
			HelperFunctions::color(RED);
			while(!InputStream.eof())
			{
				InputStream.getline(buffer,200);
				cout << buffer << endl;
			}
		}

		else
			cout << "Could not open file";
		InputStream.close();
	}
}




void Game::Play()
{
	cout <<"\n\n\n\n";
	char s[300] = "\t\t\t#####################################################\n"
				   "\t\t\t#                                                   #\n"
		           "\t\t\t#                  Text Based Game                  #\n"
		           "\t\t\t#                                                   #\n"
		           "\t\t\t#####################################################";

    HelperFunctions::color(RED);
	cout << s;
	cout <<"\n\n\n";
	displayStory();

	char functionName[30];
	bool exit_Castle = false;
	playerPtr->Look();

	do
	{
		HelperFunctions::color(YELLOW);
		cout << "\n\nWhat do you want to do : ";

		char fullCommand[30];
		cin.getline(fullCommand,30);

		//Converting all the characters of fullCommand to UpperCase
		HelperFunctions::charactersCase(fullCommand);


		char command[15];

		int i = 0;

		for (i = 0; fullCommand[i] != '\0' && fullCommand[i] != ' '; ++i)
		{
			functionName[i] = fullCommand[i];
		}

		functionName[i] = '\0';

		//Check for LOOK and EXIT Command's Case
		if(strlen(functionName) != strlen(fullCommand))
			strcpy_s(command , 15 , fullCommand + i + 1);


		if ( strcmp(functionName,	 "MOVE") == 0)
		{
			if (playerPtr-> Move(command , exit_Castle))
				playerPtr->Look();

			if (exit_Castle == true)
			{
					gameCheck();
			}
		}


		else if ( strcmp(functionName,	 "PICK") == 0)
			playerPtr->Pick(command);

		else if ( strcmp(functionName,	 "DROP") == 0)
			playerPtr->Drop(command);

		else if ( strcmp(functionName,	 "LOOK") == 0)
			playerPtr->Look();


		else if ( strcmp(functionName,	 "ATTACK") == 0)
		{
			if(playerPtr->Attack(command))
			{
				castlePtr->HiddenRoomsUnlocker(command , monstersPtr);
			}
			else if(playerPtr->getCurrentState() == false)
				PlayerDead();
		}

		else if(strcmp (functionName , "EXIT") == 0)
		{
			playerPtr->Exit();
		}
		else
		{
			HelperFunctions::color(RED);
			cout << "\nINVALID COMMAND . Please enter a Valid Command .";
		}
	}
	while (playerPtr->getCurrentState() && !exit_Castle && (strcmp (functionName , "EXIT") != 0));
}

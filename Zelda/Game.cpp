#include "pch.h"
#include "Game.h"

Game::Game()
{
	//Creating Items for the Game
	itemsPtr[0] = new Treasure("GOLDEN EGG", 500);
	itemsPtr[1] = new Treasure("GOLDEN CHALICE", 500);
	itemsPtr[2] = new Treasure("PROOF", 1000);
	itemsPtr[3] = new Weapon("SHIELD");
	itemsPtr[4] = new Weapon("DAGGER");


	//Creating Monsters for the Game
	monstersPtr[0] = new Monster("MEDUSA", itemsPtr[3]);
	monstersPtr[1] = new Monster("DRACULA", itemsPtr[4]);


	//Creating Princess for the Game
	princessPtr = new Princess;


	//Creating Castle for the Game
	castlePtr = new Castle;


	//Placing items and monsters in rooms and linking them
	castlePtr->LinkRoomsWithOtherThings(itemsPtr, monstersPtr, princessPtr);
	castlePtr->setDescriptionOfRooms();
	castlePtr->setNumbersofRooms();

	//Code to get the name of the Player
	char username[20];
	HelperFunctions::color(YELLOW);
	cout << "Enter your name : ";
	cin.getline(username, 20);


	//Creating Player for the Game
	playerPtr = new Player(username, castlePtr->getRoom(1));
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

		while (!InputStream.eof())
		{

			InputStream.getline(buffer, 200);
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

		while (!InputStream.eof())
		{
			char buffer[200];

			while (!InputStream.eof())
			{

				InputStream.getline(buffer, 200);
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
	if (playerPtr->getPrincess_Pointer())
	{
		ifstream InputStream("EndWin.txt");
		if (InputStream.is_open())
		{
			HelperFunctions::color(AQUA);

			char buffer[200];

			while (!InputStream.eof())
			{
				InputStream.getline(buffer, 200);
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
			while (!InputStream.eof())
			{
				InputStream.getline(buffer, 200);
				cout << buffer << endl;
			}
		}

		else
			cout << "Could not open file";
		InputStream.close();
	}
}

void Game::Ending() {
	int cash = playerPtr->getCash();
	cout << "You have " << cash << " Gold!" << endl;
	if (cash >= 2000) {
		cout << "WOW!You collected all the treasure in castle and you are so rich now! You married with Princess and set up a kingdom with her in Europe!" << endl;
	}
	else if (cash >= 500) {
		cout << "You collect some treasure but not all of them. You brought Princess back to hometown. You sold your weapon, aramor and treasure. You enjoyed the rest of your life with Pirncess as a oridiany man" << endl;
	}
	else {
		cout << "You did not bring any treasure out of the castle. You cannot pay for the Ship ticket back to your home. Instead, you sneak into a random ship with princess. However,the destination of this ship is the Wonderland North Koera. You spent the rest of your life as a labor" << endl;
	}

}


void Game::Play()
{
	cout << "\n\n\n\n";
	char s[300] = "\t\t\t#####################################################\n"
		"\t\t\t#                                                   #\n"
		"\t\t\t#                  Text Based Game                  #\n"
		"\t\t\t#                                                   #\n"
		"\t\t\t#####################################################";

	HelperFunctions::color(RED);
	cout << s;
	cout << "\n\n\n";
	displayStory();

	char functionName[30];
	bool exit_Castle = false;
	playerPtr->Look();
	int round = 1;//keep tracking the round
	do
	{
		HelperFunctions::color(YELLOW);
		cout << "\n\nWhat do you want to do : ";

		char fullCommand[30];
		cin.getline(fullCommand, 30);

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
		if (strlen(functionName) != strlen(fullCommand))
			strcpy_s(command, 15, fullCommand + i + 1);


		if (strcmp(functionName, "MOVE") == 0)
		{
			while (round == 1 && strcmp(command, "WEST") == 0) {//make sure user does not move west and quit game at first round
				int choice;
				cout << "Are you sure you want to move west and quit this game?(1.Yes 2.No)" << endl;
				cin >> choice;
				cin.ignore(256, '\n');
				cin.clear();
				if (choice == 1) {
					break;
				}
				else {
					cout << "Please input direction again(South,East)" << endl;//ask user to input direction again
					cin >> command;
					cin.ignore(256, '\n');
					cin.clear();
					HelperFunctions::charactersCase(command);
				}
			}
			if (playerPtr->Move(command, exit_Castle))
				playerPtr->Look();

			if (exit_Castle == true)
			{
				gameCheck();
			}
		}

		else if (strcmp(functionName, "PICK") == 0)
			playerPtr->Pick(command);

		else if (strcmp(functionName, "DROP") == 0)
			playerPtr->Drop(command);

		else if (strcmp(functionName, "LOOK") == 0)
			playerPtr->Look();


		else if (strcmp(functionName, "ATTACK") == 0)
		{
			if (playerPtr->Attack(command))
			{
				castlePtr->HiddenRoomsUnlocker(command, monstersPtr);
			}
			else if (playerPtr->getCurrentState() == false)
				PlayerDead();
		}

		else if (strcmp(functionName, "EXIT") == 0)
		{
			playerPtr->Exit();
		}
		else
		{
			HelperFunctions::color(RED);
			cout << "\nINVALID COMMAND . Please enter a Valid Command .";
		}
		round++;//increase the round number
	} while (playerPtr->getCurrentState() && !exit_Castle && (strcmp(functionName, "EXIT") != 0));
	cout << "You finished the game in " << round << "rounds!" << endl;
	if (princessPtr->getAlongState() == true) {//only player rescue princess successfully, he will use the cash and have extra endings
		Ending();
	}
}
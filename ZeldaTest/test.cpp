#include "pch.h"

#include "../Zelda/HelperFunctions.cpp"
#include "../Zelda/Item.cpp"
#include "../Zelda/Treasure.cpp"
#include "../Zelda/Weapon.cpp" 
#include "../Zelda/Monster.cpp"
#include "../Zelda/Princess.cpp"
#include "../Zelda/Room.cpp"
#include "../Zelda/Castle.cpp"
#include "../Zelda/Player.cpp"
#include "../Zelda/Game.cpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

//---------------------Player------------------------


      //---------------------Player is alive brute force------------------------

TEST(PlayerIsAlive,PlayerConstructor) {
  Room * room = new Room();
  Player * playa = new Player("Steve", room );
  EXPECT_TRUE(playa->getCurrentState());

  delete playa;
  delete room;
}

/*Manually killing player wth set current state
*/
TEST(PlayerIsAlive,PlayerSetState){
  Room * room = new Room();
  Player * playa = new Player("Steve", room );

  EXPECT_TRUE(playa->getCurrentState());
  playa->setCurrentState(false);
  EXPECT_FALSE(playa->getCurrentState());

  delete playa;
  delete room;
}


      //---------------------Player Attack mechanic------------------------
/*Attack function sent inccorrrect name of monster,
should not result in the monster getting killed.*/
TEST(PlayerAttackMechanic, TypoPlayerAttackWithWeaponAndMonster) {
	Room * room = new Room();
	Weapon * dummyWeapon = new Weapon("paradox");
	Player * playa = new Player("Steve", room);
	Monster * dummy = new Monster("Steve's mom", dummyWeapon);
	room->setItemsPresent(0, dummyWeapon);
	playa->Pick("paradox");

	room->setMonsterPresent(dummy);
	EXPECT_TRUE(playa->getCurrentState());
	EXPECT_FALSE(playa->Attack("Stacy's mom")); // here we specify an incorrect string
	EXPECT_TRUE(playa->getCurrentState());
	EXPECT_TRUE(dummy->getLivingState());

	delete dummyWeapon;
	delete dummy;
	delete playa;
	delete room;
}

/*Attack function sent incorrect weapon,
should result in a failed attack, resulting in death of the player*/
TEST(PlayerAttackMechanic,WrongWeaponAttack) {
	Room * room = new Room();
	Weapon * realWeapon = new Weapon("rocket launcher");
	Weapon * dummyWeapon = new Weapon("NERF blaster");
	Player * playa = new Player("Steve", room);
	Monster * dummy = new Monster("Cyclops", realWeapon);

	room->setItemsPresent(0, dummyWeapon);
	room->setItemsPresent(1, realWeapon);

	playa->Pick("NERF blaster");


	room->setMonsterPresent(dummy);
	EXPECT_TRUE(playa->getCurrentState());
	EXPECT_FALSE(playa->Attack("Cyclops")); // we dont have correct weapon, should die
	EXPECT_FALSE(playa->getCurrentState());
	EXPECT_TRUE(dummy->getLivingState());

	delete dummyWeapon;
	delete realWeapon;
	delete dummy;
	delete playa;
	delete room;
}
/*
making sure player is alive after killing monster,
also monster should be dead.
*/
TEST(PlayerAttackMechanic,PlayerAttackWithWeaponAndMonster) {
  Room * room = new Room();
  Weapon * dummyWeapon = new Weapon("paradox");
  Player * playa = new Player("Steve", room );
  Monster * dummy = new Monster("Steve's mom",dummyWeapon);
  room->setItemsPresent(0,dummyWeapon);
  playa->Pick("paradox");

  room->setMonsterPresent(dummy);
  EXPECT_TRUE(dummy->getLivingState());
  EXPECT_TRUE(playa->getCurrentState());
  EXPECT_TRUE(playa->Attack("Steve's mom"));
  EXPECT_TRUE(playa->getCurrentState());
  EXPECT_FALSE(dummy->getLivingState());

  delete dummyWeapon;
  delete dummy;
  delete playa;
  delete room;
}
/*
Player should not be able to attack same monster twice
*/
TEST(PlayerAttackMechanic,PlayerAttackTwiceWithWeaponAndMonster) {
  Room * room = new Room();
  Weapon * dummyWeapon = new Weapon("paradox");
  Player * playa = new Player("Steve", room );
  Monster * dummy = new Monster("Steve's mom",dummyWeapon);
  room->setItemsPresent(0,dummyWeapon);
  playa->Pick("paradox");
  room->setMonsterPresent(dummy);

  EXPECT_TRUE(dummy->getLivingState());
  EXPECT_TRUE(playa->getCurrentState());
  EXPECT_TRUE(playa->Attack("Steve's mom"));

  EXPECT_TRUE(playa->getCurrentState());
  EXPECT_FALSE(dummy->getLivingState());
  EXPECT_FALSE(playa->Attack("Steve's mom"));
  EXPECT_FALSE(dummy->getLivingState());

  delete dummyWeapon;
  delete dummy;
  delete playa;
  delete room;
}

/*Attacking monster without a weapon, should die
*/
TEST(PlayerAttackMechanic,PlayerAttackWithNoWeaponAndMonster) {
  Room * room = new Room();
  Player * playa = new Player("Steve", room );
  Weapon * dummyWeapon = new Weapon("paradox");

  Monster * dummy = new Monster("Steve's mom",dummyWeapon);

  room->setMonsterPresent(dummy);
  EXPECT_TRUE(dummy->getLivingState());
  EXPECT_TRUE(playa->getCurrentState());

  EXPECT_FALSE(playa->Attack("Steve's mom"));

  EXPECT_TRUE(dummy->getLivingState());
  EXPECT_FALSE(playa->getCurrentState());

  delete dummy;
  delete playa;
  delete room;
}
/*Attacking a room with no monster or weapon, should print out and cancel.
*/
TEST(PlayerAttackMechanic, PlayerAttackWithNoWeaponAndNoMonster) {
	Room * room = new Room();
	Player * playa = new Player("Steve", room);

	EXPECT_TRUE(playa->getCurrentState());
	EXPECT_FALSE(playa->Attack("Steve's mom"));
	EXPECT_TRUE(playa->getCurrentState());

	delete playa;
	delete room;
}

/*

*/
TEST(PlayerItemFeatures,PlayerPickUpTooMany){

	const int numTreasure = 15;
	char buffer[50];
  Room * room = new Room();
  Room * room2 = new Room();
  Room * room3 = new Room();
  Room * room4 = new Room();

  Player * playa = new Player("Steve", room);
  Treasure* stuff[numTreasure];
  bool f = false;

  room->setNorth(room2);
  room2->setNorth(room3);
  room3->setNorth(room4);

  Weapon * dummyWeapon = new Weapon("paradox");
  Treasure * dummyTreasure = new Treasure("Flashlight", 50);
  Treasure * dummyTreasure1 = new Treasure("Torch", 5000);
  Treasure * dummyTreasure2 = new Treasure("Pile of Poo",5000);

  for(int i=0;i< numTreasure;i++){
	  sprintf(buffer, "thing%i", i);
    stuff[i]=new Treasure(buffer,1000);
  }
  for(int i=0;i<5;i++){
  	sprintf(buffer, "thing%i", i);
    room2->setItemsPresent(i,stuff[i]);
  }
  for(int i=0;i<5;i++){
  	sprintf(buffer, "thing%i", i+5);
    room3->setItemsPresent(i,stuff[i+5]);
  }
  for (int i = 0; i < 5; i++) {
	  sprintf(buffer, "thing%i", i + 10);
	  room4->setItemsPresent(i, stuff[i+10]);
  }

  room->setItemsPresent(0,dummyWeapon);
  room->setItemsPresent(1,dummyTreasure);
  room->setItemsPresent(2,dummyTreasure1);
  room->setItemsPresent(3,dummyTreasure2);

  playa->Pick("paradox");
  playa->Pick("Flashlight");
  playa->Pick("Torch");
  playa->Pick("Pile of Poo");

  playa->Move("NORTH",f);
  for(int i=0;i<5;i++){
	  sprintf(buffer, "thing%i", i);
      playa->Pick(buffer);

  }
  playa->Move("NORTH",f);
  for(int i=0;i<5;i++){
	  sprintf(buffer, "thing%i", i+5);
      playa->Pick(buffer);

  }
  playa->Move("NORTH", f);
  EXPECT_EQ(16050, playa->getCash());
  EXPECT_NE(20050, playa->getCash()); // this means they picked up all 7 items
 // playa->Look();

  for(int i=0;i< numTreasure;i++){
    delete stuff[i];
  }
  delete dummyWeapon;
  delete dummyTreasure;
  delete dummyTreasure1;
  delete dummyTreasure2;
  delete room;
  delete room2;
  delete room3;
  delete room4;
  delete playa;
}


TEST(HelperFunctions,caseTest){

  char letters[50];
  memset(letters,'\0',50);


  strcpy(letters,"abcdEF");
  HelperFunctions::charactersCase(letters);
  EXPECT_STREQ(letters,"ABCDEF\0");

  strcpy(letters,"ABCDEF");
  HelperFunctions::charactersCase(letters);
  EXPECT_STREQ(letters,"ABCDEF\0");

  strcpy(letters,"abc0ef");

  HelperFunctions::charactersCase(letters);
  EXPECT_STREQ(letters,"ABC0EF\0");

  strcpy(letters,"abc0ef");
  HelperFunctions::charactersCase(letters);
  EXPECT_STRNE(letters,"abc0ef\0");

}
//-----------------------END------------------------
//---------------------Player------------------------


//---------------------Room------------------------

/* Should return the integer enumeration for cardinal direcions*/
TEST(RoomDirectionIndex, Capital) {
	Room* room = new Room();

	// 0 = North
	// 1 = South
	// 2 = East
	// 3 = West

	EXPECT_EQ(0, room->directionIndex("NORTH"));
	EXPECT_EQ(1, room->directionIndex("SOUTH"));
	EXPECT_EQ(2, room->directionIndex("EAST"));
	EXPECT_EQ(3, room->directionIndex("WEST"));

	delete room;
}

/* Should return the integer enumeration for cardinal direcions*/
TEST(RoomDirectionIndex, MixedCase) {
	Room* room = new Room();

	EXPECT_EQ(0, room->directionIndex("noRth"));
	EXPECT_EQ(1, room->directionIndex("SoUtH"));
	EXPECT_EQ(2, room->directionIndex("EaSt"));
	EXPECT_EQ(3, room->directionIndex("WesT"));

	delete room;
}

/* Should return an error code for the direction index*/
TEST(RoomDirectionIndex, WrongWords) {
	Room* room = new Room();

	EXPECT_EQ(-1, room->directionIndex("lkafsjlkdsajflsafd"));
	EXPECT_EQ(-1, room->directionIndex("ioewuroijsafjkhsdkjfahs"));
	EXPECT_EQ(-1, room->directionIndex("sjdkafhkjsn,nvxzc,mcnkds"));
	EXPECT_EQ(-1, room->directionIndex("huiuysiafhsdakjfhdakj"));

	delete room;
}

/* Should return an error code for the direction index*/
TEST(RoomDirectionIndex, SpecialCharacters) {
	Room* room = new Room();

	EXPECT_EQ(-1, room->directionIndex("%*(#&%(*#&%*(#$@&%$"));
	EXPECT_EQ(-1, room->directionIndex("98375@(*#%&*(&@#$*(%3"));
	EXPECT_EQ(-1, room->directionIndex("(*#&%(*#$%&(*#&#$%*(#$,n"));
	EXPECT_EQ(-1, room->directionIndex("*&(#*%&#*(%&#$*(%#$&%#(*"));

	delete room;
}

/* Should return a string representation of the cardinal direction of integers*/
TEST(RoomDirectionName, IntegerInput) {
	Room* room = new Room();

	EXPECT_STREQ("North", room->directionName(0));
	EXPECT_STREQ("South", room->directionName(1));
	EXPECT_STREQ("East",  room->directionName(2));
	EXPECT_STREQ("West", room->directionName(3));

	delete room;
}

/*Should return an empty string because the indicated integer is outside of range*/
TEST(RoomDirectionName, OutsideNormalRange) {
	Room* room = new Room();

	EXPECT_STREQ("", room->directionName(4));

	delete room;
}

/*Should return an empty string because the indicated value is the wrong type*/
TEST(RoomDirectionName, FloatInput) {
	Room* room = new Room();

	EXPECT_STREQ("", room->directionName(4.0));

	delete room;
}

/*Should set the paths betweens rooms.  If failure, check that the rooms are not given paths initially*/
TEST(RoomGettersSetters, SurroundingRooms) {
	Room* room = new Room();
	Room* room2 = new Room();
	Room* room3 = new Room();
	Room* room4 = new Room();
	Room* room5 = new Room();

	room->setNorth(room2);
	room->setSouth(room3);
	room->setEast(room4);
	room->setWest(room5);

	EXPECT_EQ(room2, room->getPaths()[0]);
	EXPECT_EQ(room3, room->getPaths()[1]);
	EXPECT_EQ(room4, room->getPaths()[2]);
	EXPECT_EQ(room5, room->getPaths()[3]);

	// Reset to another value
	room->setNorth(room5);
	room->setSouth(room4);
	room->setEast(room3);
	room->setWest(room2);

	EXPECT_EQ(room5, room->getPaths()[0]);
	EXPECT_EQ(room4, room->getPaths()[1]);
	EXPECT_EQ(room3, room->getPaths()[2]);
	EXPECT_EQ(room2, room->getPaths()[3]);


	delete room;
	delete room2;
	delete room3;
	delete room4;
	delete room5;
}

/* Tests a very long description for the room and a typical string length.*/
TEST(RoomGettersSetters, Description) {
	Room* room = new Room();

	room->setDesription("Room0");

	EXPECT_STREQ("Room0", room->getDescription());

	char const* name = "57572983570832975032485032498739873047258347598275098327503428753409285732409857342089"
		"5834285-3492853420958324-0958342-958342-095834-0258342-09583-095832-589324";

	room->setDesription(name);

	EXPECT_STREQ(name, room->getDescription());

	delete room;
}

/* Tests that the room class can have it's items set and the room filled up.*/
TEST(RoomGettersSetters, Items) {
	Room* room = new Room();
	Item* weapon = new Weapon("weaponWEAPON");
	Item* treasure = new Treasure("TESTtresureName", INT_MAX);

	EXPECT_EQ(false, room->isRoomFull());

	room->setItemsPresent(0, weapon);
	room->setItemsPresent(1, treasure);
	room->setItemsPresent(2, weapon);
	room->setItemsPresent(3, treasure);
	room->setItemsPresent(4, weapon);
	room->setItemsPresent(5000, treasure);

	Item** items = room->getItemsPresent();

	EXPECT_EQ(weapon, items[0]);
	EXPECT_EQ(treasure, items[1]);
	EXPECT_EQ(weapon, items[2]);
	EXPECT_EQ(treasure, items[3]);
	EXPECT_EQ(weapon, items[4]);
	//EXPECT_EQ(treasure, items[5000]);

	EXPECT_EQ(true, room->isRoomFull());

	delete room;
	delete weapon;
	delete treasure;
}

/* Tests that the room can have its princess and monster set.  Checks that their names are correct.  */
TEST(RoomGettersSetters, PrincessMonster) {
	Room* room = new Room();
	Item* weapon = new Weapon("weaponWEAPON");
	Monster* monster = new Monster("TESTmonsterName", weapon);
	Princess* princess = new Princess();

	room->setPrincessPresent(princess);
	EXPECT_EQ(princess, room->getPrincessPresent());

	room->setMonsterPresent(monster);
	EXPECT_EQ(monster, room->getMonsterPresent());

	delete room;
	delete weapon;
	delete monster;
	delete princess;
}

/* Checks that the room number can be successfully set and retrieved.*/
TEST(RoomGettersSetters, RoomNumber) {
	Room* room = new Room();

	int number = 0;
	room->setRoomNumber(0);
	EXPECT_EQ(number, room->getRoomNumber());

	number = 9437489724;
	room->setRoomNumber(number);
	EXPECT_EQ(number, room->getRoomNumber());

	number = -100;
	room->setRoomNumber(number);
	EXPECT_EQ(number, room->getRoomNumber());
}

//---------------------Castle------------------------

/* Tests if the castle can link rooms 5 and 8 by adding eachother as paths. */
TEST(CastleLinking, LinkRoom5and8) {
	Castle* castle = new Castle();

	// paths[0] = North
	// paths[1] = South
	// paths[2] = East
	// paths[3] = West

	// Check that the rooms are not currently linked
	Room* room5Paths = castle->getRoom(5)->getPaths()[1];
	Room* room8Paths = castle->getRoom(8)->getPaths()[0];

	EXPECT_EQ(room5Paths, nullptr);
	EXPECT_EQ(room8Paths, nullptr);

	// Link the rooms
	castle->LinkRoom5and8();

	// Test that they were successfully linked
	room5Paths = castle->getRoom(5)->getPaths()[1];
	room8Paths = castle->getRoom(8)->getPaths()[0];

	EXPECT_EQ(room5Paths, castle->getRoom(8));
	EXPECT_EQ(room8Paths, castle->getRoom(5));

	delete castle;
}

/* Tests if the castle can link rooms 6 and 9 by adding eachother as paths. */
TEST(CastleLinking, LinkRoom6and9) {
	Castle* castle = new Castle();

	// Check that the rooms are not currently linked
	Room* room6Paths = castle->getRoom(6)->getPaths()[1];
	Room* room9Paths = castle->getRoom(9)->getPaths()[0];

	EXPECT_EQ(room6Paths, nullptr);
	EXPECT_EQ(room9Paths, nullptr);

	// Link the rooms
	castle->LinkRoom6and9();

	// Test that they were successfully linked
	room6Paths = castle->getRoom(6)->getPaths()[1];
	room9Paths = castle->getRoom(9)->getPaths()[0];

	EXPECT_EQ(room6Paths, castle->getRoom(9));
	EXPECT_EQ(room9Paths, castle->getRoom(6));

	delete castle;
}

/* Tests if the castle can run its setup function with null input. */
TEST(CastleLinking, LinkAllRoomsNull) {
	Castle* castle = new Castle();

	castle->LinkRoomsWithOtherThings(nullptr, nullptr, nullptr);

	EXPECT_EQ(castle->getRoom(1)->getPaths()[2], castle->getRoom(2));

	delete castle;
}

/* Tests if the castle can run its setup function with full input. */
TEST(CastleLinking, LinkAllRooms) {
	Castle* castle = new Castle();
	Item** itemsPtr = new Item*[5];
	itemsPtr[0] = new Treasure("GOLDEN EGG", 500000);
	itemsPtr[1] = new Treasure("GOLDEN CHALICE", 500000);
	itemsPtr[2] = new Treasure("PROOF", 1000000);
	itemsPtr[3] = new Weapon("SHIELD");
	itemsPtr[4] = new Weapon("DAGGER");
	Monster** monstersPtr = new Monster*[5];
	monstersPtr[0] = new Monster("MEDUSA", itemsPtr[3]);
	monstersPtr[1] = new Monster("DRACULA", itemsPtr[4]);
	Princess* princessPtr = new Princess;

	castle->LinkRoomsWithOtherThings(itemsPtr, monstersPtr, princessPtr);

	EXPECT_EQ(castle->getRoom(1)->getPaths()[2], castle->getRoom(2));

	delete castle;
	delete [] itemsPtr;
	delete [] monstersPtr;
	delete princessPtr;
}

/* Tests that the castle can set room numbers for all of its rooms. */
TEST(CastleGetSet, roomNumbers) {
	Castle* castle = new Castle();

	castle->setNumbersofRooms();

	for (int ii = 1; ii < 10; ++ii) {
		EXPECT_EQ(castle->getRoom(ii)->getRoomNumber(), ii);
	}

	delete castle;
}

/* Tests the get room function by getting a room outside of the range. */
TEST(CastleGetSet, getRooms100) {
	Castle* castle = new Castle();

	castle->setNumbersofRooms();

	EXPECT_EQ(castle->getRoom(100), nullptr);

	delete castle;
}

/* Tests the get room function by getting a room of negative index. */
TEST(CastleGetSet, getRoomsNegative) {
	Castle* castle = new Castle();

	castle->setNumbersofRooms();

	EXPECT_EQ(castle->getRoom(-1), nullptr);

	delete castle;
}

/* Tests the get room function by getting rooms in the indices [1, 10] */
TEST(CastleGetSet, getRooms1Through10) {
	Castle* castle = new Castle();

	castle->setNumbersofRooms();

	for (int ii = 1; ii < 10; ++ii) {
		EXPECT_EQ(castle->getRoom(ii)->getRoomNumber(), ii);
	}

	delete castle;
}


//---------------------Monster------------------------
TEST(MonsterConstructor, ConstructorWithParameter) {
	Weapon* weapon = new Weapon("weapon");
	Monster* monster = new Monster("monster", weapon);
	EXPECT_STREQ("monster", monster->getMonsterName());
	EXPECT_STREQ("weapon", monster->getKillingWeapon()->getItemName());
	EXPECT_EQ(true, monster->getLivingState());
	delete monster;
	delete weapon;
}

TEST(MonsterConstructor, ConstructorWithoutParameter) {
	Monster* monster = new Monster();
	EXPECT_EQ(nullptr, monster->getMonsterName());
	EXPECT_EQ(nullptr, monster->getKillingWeapon());
	EXPECT_EQ(true, monster->getLivingState());
	delete monster;
}

TEST(MonsterGetterSetter,WeaponGetSet) {
	Weapon* weapon = new Weapon("weapon");
	Monster* monster = new Monster();
	monster->setKillingWeapon(weapon);
	EXPECT_STREQ("weapon", monster->getKillingWeapon()->getItemName());
	delete monster;
	delete weapon;
}

TEST(MonsterGetterSetter, LivingGetSet) {
	Monster* monster = new Monster();
	monster->setLivingState(false);
	EXPECT_EQ(false, monster->getLivingState());
	delete monster;
}

TEST(MonsterGetterSetter, NameGetSet) {
	Monster* monster = new Monster("monster", nullptr);
	//monster has not setter for name
	EXPECT_STREQ("monster",monster->getMonsterName());
	delete monster;
}

//---------------------Princess------------------------
TEST(PrincessConstructor, Constructor) {
	Princess* princess=new Princess();
	EXPECT_EQ(true,princess->getLivingState());
	delete princess;
}

TEST(PrincessGetSet, LivingState) {
	Princess* princess=new Princess();
	princess->setLivingState(false);
	EXPECT_EQ(false,princess->getLivingState());
	delete princess;
}


//---------------------Treasure------------------------

TEST(TreasureCreation, StandardCase) {
	Treasure* treasure = new Treasure("The Holy Grail", 62);

	EXPECT_STREQ("The Holy Grail", treasure->getItemName());
	EXPECT_EQ(62, treasure->getWorth());

	delete treasure;
}

TEST(TreasureCreation, LongName) {
	Treasure* treasure = new Treasure("The Holy Grail is a really great thing to have perhaps we should go on a long quest for it and make the best movie in the world about said quest", 0);

	EXPECT_STREQ("The Holy Grail is a really great thing to have perhaps we should go on a long quest for it and make the best movie in the world about said quest", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, AllCaps) {
	Treasure* treasure = new Treasure("THE HOLY GRAIL", 0);

	EXPECT_STREQ("THE HOLY GRAIL", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, MixedCases) {
	Treasure* treasure = new Treasure("ThE HoLy GrAiL", 0);

	EXPECT_STREQ("ThE HoLy GrAiL", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, SpecialCharacters) {
	Treasure* treasure = new Treasure("\n\t\0", 0);

	EXPECT_STREQ("\n\t\0", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, NoInput) {
	Treasure* treasure = new Treasure("", 0);

	EXPECT_STREQ("", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, WhiteSpace) {
	Treasure* treasure = new Treasure("		", 0);

	EXPECT_STREQ("		", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, ZeroWorth) {
	Treasure* treasure = new Treasure("The Holy Grail", 0);

	EXPECT_EQ(0, treasure->getWorth());

	delete treasure;
}

TEST(TreasureCreation, NegativeWorth) {
	Treasure* treasure = new Treasure("The Holy Grail", -1);

	EXPECT_EQ(-1, treasure->getWorth());

	delete treasure;
}

TEST(TreasureCreation, HugeWorth) {
	Treasure* treasure = new Treasure("The Holy Grail", 10000000);

	EXPECT_EQ(10000000, treasure->getWorth());

	delete treasure;
}

TEST(TreasureCreation, FractionalWorth) {
	Treasure* treasure = new Treasure("The Holy Grail", 0.5);

	EXPECT_EQ(0.0, treasure->getWorth());

	delete treasure;
}

//---------------------Weapon------------------------

TEST(WeaponCreation, StandardCase) {
	Weapon* weapon = new Weapon("Gurthang");

	EXPECT_STREQ("Gurthang", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, AllCaps) {
	Weapon* weapon = new Weapon("A DUCK");

	EXPECT_STREQ("A DUCK", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, LongName) {
	Weapon* weapon = new Weapon("How do you know she is a witch? She looks like one! Bring her forward. I'm not a witch. I'm not a witch. But you are dressed as one. They dressed me up like this. No, no we didn't -- no. And this isn't my nose, it's a false one.");

	EXPECT_STREQ("How do you know she is a witch? She looks like one! Bring her forward. I'm not a witch. I'm not a witch. But you are dressed as one. They dressed me up like this. No, no we didn't -- no. And this isn't my nose, it's a false one.", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, MixedCases) {
	Weapon* weapon = new Weapon("a duCK");

	EXPECT_STREQ("a duCK", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, NoInput) {
	Weapon* weapon = new Weapon("");

	EXPECT_STREQ("", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, WhiteSpace) {
	Weapon* weapon = new Weapon("	");

	EXPECT_STREQ("	", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, SpecialCharacters) {
	Weapon* weapon = new Weapon("\n\t\0");

	EXPECT_STREQ("\n\t\0", weapon->getItemName());

	delete weapon;
}

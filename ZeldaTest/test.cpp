#include "pch.h"
#include "../Zelda/Zelda.cpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


//---------------------Room------------------------

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

TEST(RoomDirectionIndex, MixedCase) {
	Room* room = new Room();

	EXPECT_EQ(0, room->directionIndex("noRth"));
	EXPECT_EQ(1, room->directionIndex("SoUtH"));
	EXPECT_EQ(2, room->directionIndex("EaSt"));
	EXPECT_EQ(3, room->directionIndex("WesT"));

	delete room;
}

TEST(RoomDirectionName, IntegerInput) {
	Room* room = new Room();

	EXPECT_STREQ("North", room->directionName(0));
	EXPECT_STREQ("South", room->directionName(1));
	EXPECT_STREQ("East",  room->directionName(2));
	EXPECT_STREQ("West", room->directionName(3));

	delete room;
}

TEST(RoomDirectionName, OutsideNormalRange) {
	Room* room = new Room();

	EXPECT_STREQ("", room->directionName(4));

	delete room;
}

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
	EXPECT_EQ(treasure, items[5000]);

	EXPECT_EQ(true, room->isRoomFull());

	delete room;
	delete weapon;
	delete treasure;
}

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

TEST(CastleGetSet, roomNumbers) {
	Castle* castle = new Castle();

	castle->setNumbersofRooms();

	for (int ii = 1; ii < 10; ++ii) {
		EXPECT_EQ(castle->getRoom(ii)->getRoomNumber(), ii);
	}
	
	delete castle;
}

TEST(CastleLinking, LinkRoomsWithOtherThings) {
	Castle* castle = new Castle();

	castle->LinkRoomsWithOtherThings(nullptr, nullptr, nullptr);

	EXPECT_EQ(castle->getRoom(1)->getPaths()[2], castle->getRoom(2));

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
}

TEST(PrincessGetSet, LivingState) {
	Princess* princess=new Princess();
	princess->setLivingState(false);
	EXPECT_EQ(false,princess->getLivingState());
}



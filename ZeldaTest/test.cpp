#include "pch.h"
#include "../Zelda/Zelda.cpp"

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
	EXPECT_FALSE(playa->Attack("Stacy's mom"));
	EXPECT_TRUE(playa->getCurrentState());
	EXPECT_TRUE(dummy->getLivingState);

	delete dummyWeapon;
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
  Monster * dummy = new Monster("Steves mom",dummyWeapon);
  room->setItemsPresent(0,dummyWeapon);
  playa->Pick("paradox");

  room->setMonsterPresent(dummy);
  EXPECT_TRUE(dummy->getLivingState);
  EXPECT_TRUE(playa->getCurrentState());
  EXPECT_TRUE(playa->Attack("Steve's mom"));
  EXPECT_TRUE(playa->getCurrentState());
  EXPECT_FALSE(dummy->getLivingState);

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
  Monster * dummy = new Monster("Steves mom",dummyWeapon);
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
  Weapon * dummyWeapon = new Weapon("paradox");
  Player * playa = new Player("Steve", room );
  Monster * dummy = new Monster("Steve's mom",dummyWeapon);

  room->setMonsterPresent(dummy);
  EXPECT_TRUE(dummy->getLivingState());
  EXPECT_TRUE(playa->getCurrentState());

  EXPECT_FALSE(playa->Attack("Steve's mom"));

  EXPECT_TRUE(dummy->getLivingState());
  EXPECT_FALSE(playa->getCurrentState());

  delete dummyWeapon;
  delete dummy;
  delete playa;
  delete room;
}
/*Attacking a room with no monster or weapon, should print out and cancel.
*/
TEST(PlayerAttackMechanic, PlayerAttackWithNoWeaponAndNoMonster) {
	Room * room = new Room();
	Weapon * dummyWeapon = new Weapon("paradox");
	Player * playa = new Player("Steve", room);
	Monster * dummy = new Monster("Steve's mom", dummyWeapon);

	EXPECT_TRUE(playa->getCurrentState());
	EXPECT_FALSE(playa->Attack("Steve's mom"));
	EXPECT_TRUE(playa->getCurrentState());

	delete dummyWeapon;
	delete dummy;
	delete playa;
	delete room;
}

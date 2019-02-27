#include "pch.h"
#include "../Zelda/Zelda.cpp"

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
  Monster * dummy = new Monster("Steves mom",dummyWeapon);
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

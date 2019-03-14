#pragma once

#include "Item.h"
#include "Treasure.h"
#include "Weapon.h"
#include "Monster.h"
#include "Princess.h"
#include "Castle.h"
#include "Player.h"

class Game
{
private:
	Castle* 	castlePtr;
	Item*		itemsPtr[5];
	Princess*	princessPtr;
	Monster* 	monstersPtr[2];
	Player*		playerPtr;


public:

	Game();
	~Game();

	void	 Play();
	void	 displayStory();
	void	 PlayerDead();
	void	 gameCheck();
	void 	 Ending();
};
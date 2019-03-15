#include "pch.h"
#include "Princess.h"

Princess::Princess()
{
	is_Alive = true;
	along = false;
}



Princess::~Princess()
{

}

bool Princess::getAlongState()
{
	return along;
}



void Princess::setAlongState(bool currentAlong)
{
	along = currentAlong;
}


bool Princess::getLivingState()
{
	return is_Alive;
}

void Princess::setLivingState(bool currentState)
{
	is_Alive = currentState;
}
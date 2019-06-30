#include "Collidable.h"

bool Collidable::startContact(Collidable* col)
{
	//start of collision
	isColliding = true;
	if (isColliding == true)
	{
	}
	return isColliding;
};
bool Collidable::endContact(Collidable* col)
{
	//end of collision
	isColliding = false;
	if (isColliding == false)
	{
	}
	return isColliding;
};

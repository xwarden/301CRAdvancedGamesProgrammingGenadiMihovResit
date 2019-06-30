#pragma once
#include <Box2D\Box2D.h>
#include "Player.h"
#include "Ball.h"
#include <iostream>
#include "Collidable.h"
class ContactListener : public b2ContactListener
{
	b2Contact* cp;
public:
	ContactListener();

	void BeginContact(b2Contact* cp);
	void EndContact(b2Contact* cp);


	~ContactListener();
};


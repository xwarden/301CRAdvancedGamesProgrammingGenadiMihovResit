#include "ContactListener.h"



ContactListener::ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* cp)
{
	//fetch both coliding fictures
	b2Fixture* f1 = cp->GetFixtureA();
	b2Fixture* f2 = cp->GetFixtureB();

	//fetch the fixture bodies
	b2Body* b1 = f1->GetBody();
	b2Body* b2 = f2->GetBody();

	//fetch the user data from the bodies
	Collidable* o1 = (Collidable*)b1->GetUserData();
	Collidable* o2 = (Collidable*)b2->GetUserData();

	if (o1)
	{
		//begin collision
		o1->startContact(o2);
	}
	if (o2)
	{
		o2->startContact(o1);
	}
};
void ContactListener::EndContact(b2Contact* cp)
{
	b2Fixture* f1 = cp->GetFixtureA();
	b2Fixture* f2 = cp->GetFixtureB();

	b2Body* b1 = f1->GetBody();
	b2Body* b2 = f2->GetBody();

	Collidable* o1 = (Collidable*)b1->GetUserData();
	Collidable* o2 = (Collidable*)b2->GetUserData();

	if (o1)
	{
		//end of collision
		o1->endContact(o2);
	}
	if (o2)
	{
		o2->endContact(o1);
	}
};
ContactListener::~ContactListener()
{
}

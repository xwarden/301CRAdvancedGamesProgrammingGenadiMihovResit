#include "Walls.h"
static const float scale = 30.0f;


Walls::Walls(short group, b2World* world, float X, float Y, float mysizeX, float mysizeY)
{
	//set body parameters 
	positionX = X;
	positionY = Y;
	World = world;
	sizeX = mysizeX / 2;
	sizeY = mysizeY / 2;
	//create body
	b2BodyDef bodyDefinition;
	bodyDefinition.type = b2_staticBody;
	bodyDefinition.position.Set(positionX / scale, positionY / scale);
	bodyDefinition.fixedRotation = true;
	body = World->CreateBody(&bodyDefinition);
	body->SetUserData(this);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(sizeX / scale, sizeY / scale);
	//defining fixture
	b2FixtureDef fixtureDefinition;
	fixtureDefinition.filter.groupIndex = group;
	fixtureDefinition.shape = &boxShape;
	fixtureDefinition.density = 1.0f;
	fixtureDefinition.friction = 0.0f;
	
	body->CreateFixture(&fixtureDefinition);
}


void Walls::setPosition(float x, float y)
{
	//
	body->SetTransform(b2Vec2(x / scale, y / scale), body->GetAngle());
};

float Walls::fetchPositionX()
{
	//
	return body->GetPosition().x * scale;
};
float Walls::fetchPositionY()
{
	//
	return body->GetPosition().y * scale;
};



Walls::~Walls()
{
}

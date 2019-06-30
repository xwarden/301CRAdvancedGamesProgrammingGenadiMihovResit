#pragma once

#include <iostream>
#include<Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Collidable.h"




class Walls:public Collidable
{
	float positionX, positionY;
	float sizeX, sizeY;
	b2World* World = nullptr;
	b2Body* body = nullptr;
	b2Vec2 vel;
public:
	Walls(short group, b2World* world, float X, float Y, float mysizeX, float mysizeY);
	~Walls();

	float fetchPositionX();
	float fetchPositionY();
	void setPosition(float x, float y);
};


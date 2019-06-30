#pragma once

#include <iostream>
#include<Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Collidable.h"



class Ball :public Collidable
{   
	float positionX, positionY;
	float sizeX, sizeY;
	sf::Texture texture;
	sf::Sprite sprite;
	b2World* World = nullptr;
	b2Body* body = nullptr;
	b2Vec2 vel;
public:
	Ball(short group, b2World* world, float X, float Y, float mysizeX, float mysizeY);
	~Ball();

	sf::Sprite drawBall(std::string TextureLoc);
	void setVelocity(float velocityX, float velocityY);
	float fetchPositionX() { return body->GetPosition().x; };
	float fetchPositionY() { return body->GetPosition().y; };
	void setPosition(float x, float y) { body->SetTransform(b2Vec2(x, y), body->GetAngle()); };
	virtual bool startContact(Collidable* col)override;
	void receivePacket(float x, float y, Ball* ball);
};
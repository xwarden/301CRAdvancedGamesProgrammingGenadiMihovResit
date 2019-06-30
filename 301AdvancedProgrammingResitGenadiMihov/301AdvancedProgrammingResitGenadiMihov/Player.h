#pragma once

#include <iostream>
#include<Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>




class Player
{
	float positionX, positionY;
	float sizeX, sizeY;
	sf::Texture texture;
	sf::Sprite sprite;
	b2World* World = nullptr;
	b2Body* body = nullptr;
	b2Vec2 vel;
public:
	Player(short group, b2World* world, float X, float Y, float mysizeX, float mysizeY);
	~Player();

	sf::Sprite drawPlayer(std::string TextureLoc);
	void setVelocity(float velocityX, float velocityY);
	float fetchPositionX();
	float fetchPositionY();
	void setPosition(float x, float y);
	void receivePacket(float x, float y, Player* player);
};

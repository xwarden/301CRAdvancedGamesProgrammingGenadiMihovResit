#include <iostream>
#include <SFML/Network.hpp>
#include <Box2D/Box2D.h>
#include "ContactListener.h"
#include "Server.h"
#include "Player.h"
#include "Walls.h"


int main()
{
	//all infor about the players
	int idPlayer1 = 0;
	int idPlayer2 = 1;
	float player1x = 25.0f;
	float player1y = 250.0f;
	float player2x = 775.0f;
	float player2y = 250.0f;
	float ballx = 400.0f;
	float bally = 250.0f;
	bool test = false;

	//setting up a server 
	Server server;
	sf::Packet handShakePacket1;
	sf::Packet handShakePacket2;
	server.bindToPort(2000);
	server.connection(2000);

	//once joined make a handshake
	handShakePacket1 << idPlayer1 << player1x << player1y << player2x << player2y << ballx << bally;
	server.sendPacket(handShakePacket1, idPlayer1);


	handShakePacket2 << idPlayer2 << player1x << player1y << player2x << player2y << ballx << bally;
	server.sendPacket(handShakePacket2, idPlayer2);
	
	
	//setting up gravity for physics enviroment
	b2Vec2 gravity(0.0f, 0.0f);


	//create the world
	b2World world(gravity);



	//enabling collision listener
	ContactListener ContactListenerInstance;
	world.SetContactListener(&ContactListenerInstance);

	//setting up physics on server
	Player* player = new Player(-1, &world, player1x, player1y, 1.0f, 75.0f);
	Player* player2 = new Player(-1, &world, player2x, player2y, 1.0f, 75.0f);
	Ball* ball = new Ball(-1, &world, ballx, bally, 25.0f, 25.0f);
	Walls* topWall = new Walls(0, &world, 400.0f, -5.0f, 800.0f, 10.0f);
	Walls* bottomWall = new Walls(0, &world, 400.0f, 505.0f, 800.0f, 10.0f);

	
	//setting up network clock and the package send rate
	sf::Clock myNetworkClock;
	float packageSendRate = 60;
	float networkPackageSendInterval = 1 / packageSendRate;

	//velocity for the ball
	ball->setVelocity(2.0f,0.0f);

	//keep checkin if there is as connection
	while (server.checkConnection() != 0)
	{
		
		bool updatingMyNetwork = false;
		
		if (myNetworkClock.getElapsedTime().asSeconds() >= networkPackageSendInterval)
		{
			updatingMyNetwork = true;
			myNetworkClock.restart();
		}
		sf::Packet player1packet;
		
		if (server.receivePacket(player1packet,0))
		{
			float x, y;
			player1packet >> x >> y;
			player->receivePacket(x, y, player);
		}
		
		sf::Packet player2packet;

		if (server.receivePacket(player2packet,1))
		{
			float x, y;
			player2packet >> x >> y;
			player2->receivePacket(x, y, player2);
		}



		//if there is a connection, update positions
		if (updatingMyNetwork)
		{
			
			world.Step(1 / 60.0f, 8, 3);
			
			sf::Packet sendToP1;
			
			sendToP1 << player2->fetchPositionX() << player2->fetchPositionY() << ball->fetchPositionX() << ball->fetchPositionY();
			server.sendPacket(sendToP1, 0);

			sf::Packet sendToP2;

			sendToP2 << player->fetchPositionX() << player->fetchPositionY() << ball->fetchPositionX() << ball->fetchPositionY();
			server.sendPacket(sendToP2, 1);
		}
		
	}

	return 0;
}
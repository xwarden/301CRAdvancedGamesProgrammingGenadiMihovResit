#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Player.h"
#include "Client.h"
#include "Ball.h"
#include <chrono>
#include <thread>


int main()
{
	//
	sf::RenderWindow window(sf::VideoMode(800, 500), "My window");

	//
	sf::View localPlayerView(sf::FloatRect(0.0f, 0.0f, 800.0f, 500.0f));
	localPlayerView.setCenter(sf::Vector2f(400.0f, 250.0f));
	window.setView(localPlayerView);

	//
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Background.png");
	sf::Sprite background(backgroundTexture);
	background.setTexture(backgroundTexture);
	background.setOrigin(0.0f, 0.0f);
	background.setPosition(0.0f, 0.0f);


	//
	b2Vec2 gravity(0.0f, 0.0f);
	const float scale = 30;

	float player1posX = 0.0f;
	float player1posY = 0.0f;
	float player2posX = 0.0f;
	float player2posY = 0.0f;
	float ballX = 0.0f;
	float ballY = 0.0f;
	int myID = 0;

	//creating the world and applying a gravity modifier
	b2World world(gravity);

	//
	Client client;

	client.connect("127.0.0.1", 2000);

	//
	sf::Packet handshakepacket;
	while (client.receivePacket(handshakepacket) == false)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
	
	handshakepacket >> myID >> player1posX >> player1posY >> player2posX >> player2posY >> ballX >> ballY;

	//
	Player* player = new Player(-1, &world, player1posX, player1posY, 12.0f, 75.0f);
	Player* player2 = new Player(-1, &world, player2posX, player2posY, 12.0f, 75.0f);
	Ball* ball = new Ball(-1, &world, ballX, ballY, 25.0f, 25.0f);
	bool inputAllowed = false;

	//
	Player* thisPlayer;
	Player* otherPlayer;

	//
	if (myID == 0)
	{
		thisPlayer = player;
		otherPlayer = player2;
	}
	else
	{
		thisPlayer = player2;
		otherPlayer = player;
	}

	//
	sf::Clock myNetworkClock;
	float packageSendRate = 60;
	float networkInterval = 1 / packageSendRate;


	//
	while (window.isOpen())
	{
		//
		bool updatingMyNetwork = false;

		//
		if (myNetworkClock.getElapsedTime().asSeconds() >= networkInterval)
		{
			updatingMyNetwork = true;
			myNetworkClock.restart();
		}

		//
		sf::Packet receivedPlayerPacket;
		
		if (client.receivePacket(receivedPlayerPacket))
		{
			float player2X, player2Y, ballX, ballY;
			receivedPlayerPacket >> player2X >> player2Y >> ballX >> ballY;
			otherPlayer->receivePacket(player2X, player2Y,otherPlayer);
			ball->receivePacket(ballX, ballY, ball);
		}
		
		
		//
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::GainedFocus)
			{
				inputAllowed = true;
			}
			else if (event.type == sf::Event::LostFocus)
			{
				inputAllowed = false;
			}
		}
		//
		window.setFramerateLimit(60);
		world.Step(1 / 60.0f, 8, 3);

		//
		float minY, maxY;
		float currY = thisPlayer->fetchPositionY();
		minY = 2.0f;
		maxY = 498.0f;
		if (currY < minY)
		{
			currY = minY;
		}
		if (currY > maxY)
		{
			currY = maxY;
		}

		//
		thisPlayer->setPosition(myID == 0 ? player1posX : player2posX, currY);

		//
		window.clear(sf::Color::White);
		window.draw(background);

		//
		window.draw(player->drawPlayer("Player.png"));
		window.draw(player2->drawPlayer("Player.png"));
		window.draw(ball->drawBall("Ball.png"));

		//
		if (inputAllowed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				thisPlayer->setVelocity(0.0f, -5.0f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				thisPlayer->setVelocity(0.0f, 5.0f);
			}
			else
			{
				thisPlayer->setVelocity(0.0f, 0.0f);
			}
		}
		//
		if (updatingMyNetwork)
		{
			sf::Packet sentPlayerPacket;

			sentPlayerPacket << thisPlayer->fetchPositionX() << thisPlayer->fetchPositionY();


			client.sendPacket(sentPlayerPacket);
		}
		//
		window.display();
	}

	return 0;
}
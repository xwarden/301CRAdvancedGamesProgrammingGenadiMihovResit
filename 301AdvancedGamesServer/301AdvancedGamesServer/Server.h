#pragma once
#include <SFML/Network.hpp>
#include <iostream>
class Server
{
public:
	Server();
	void bindToPort(int port);
	void connection(int port);
	int checkConnection();
	void sendPacket(sf::Packet &packet, int id);
	bool receivePacket(sf::Packet &packet, int id);
	void disconnect();
	~Server();
private:
	sf::TcpSocket socket;
	sf::TcpSocket socket2;
	sf::TcpListener listener;
	sf::Packet packet;
};


#pragma once
#include <SFML/Network.hpp>
#include <string>

class Client
{
public:
	Client();
	void connect(std::string ip, int port);
	void sendPacket(sf::Packet &packet);
	bool receivePacket(sf::Packet &packet);
	void disconnect();

	~Client();
private:
	sf::TcpSocket socket;
	sf::Packet packet;
};


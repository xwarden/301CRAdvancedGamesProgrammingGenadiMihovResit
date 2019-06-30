#include "Client.h"



Client::Client()
{
}

void Client::connect(std::string ip, int port)
{
	//Check whether a connection is available
	sf::Socket::Status status = socket.connect(ip, port);
	if (status != sf::Socket::Done)
	{
		// error...
	}
	socket.setBlocking(false);
}

void Client::sendPacket(sf::Packet &packet)
{
	//send a packet through the socket
	socket.send(packet);
}


bool Client::receivePacket(sf::Packet &packet)
{
	//if a packet is done, receive it
	if (socket.receive(packet) == sf::Socket::Status::Done)
	{
		return true;
	}
	return false;
}

void Client::disconnect()
{
	//disconnecting
	socket.disconnect();
}

Client::~Client()
{
}

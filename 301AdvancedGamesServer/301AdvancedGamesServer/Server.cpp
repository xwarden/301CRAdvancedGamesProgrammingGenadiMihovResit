#include "Server.h"



Server::Server()
{


}

void Server::bindToPort(int port)
{
	//setup a listener on provided port
	listener.listen(port);
}

int Server::checkConnection()
{
	//if the port != 0 there is a connection
	return socket.getRemotePort();
	std::cout << "Connection Established" << std::endl;
}



void Server::connection(int port)
{
	//check if a listener has been found
	if (listener.listen(port) != sf::Socket::Done)
	{
		// error...
	}
	//accept the connection
	if (listener.accept(socket) != sf::Socket::Done)
	{
		// error...
	}
	if (listener.accept(socket2) != sf::Socket::Done)
	{
		// error...
	}
	//stop socket blocking
	socket.setBlocking(false);
	socket2.setBlocking(false);
}

void Server::sendPacket(sf::Packet &packet, int id)
{
	//send packets depending on the ID of the player
	if (id == 0)
	{
		socket.send(packet);
	}
	if (id == 1)
	{
		socket2.send(packet);
	}
}



bool Server::receivePacket(sf::Packet &packet, int id)
{
	if (id == 0)
	{
		//receive packets depending on the ID of the player
		if (socket.receive(packet) == sf::Socket::Status::Done)
		{
			return true;
		}
	}

	if (id == 1)
	{
		if (socket2.receive(packet) == sf::Socket::Status::Done)
		{
			return true;
		}
	}
	
	return false;
}

void Server::disconnect()
{
	//disconect
	socket.disconnect();
}

Server::~Server()
{
}

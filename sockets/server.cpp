#include "server.hpp"

Server::Server()
{
}

void Server::startListening(unsigned short port)
{
    listener.listen(port);
}

void Server::acceptClient()
{
    listener.accept(clientSocket);
}

void Server::sendGameData(sf::Packet& packet)
{
    clientSocket.send(packet);
}

void Server::receiveGameData(sf::Packet& packet)
{
    clientSocket.receive(packet);
}

void Server::disconnect()
{
    clientSocket.disconnect();
}

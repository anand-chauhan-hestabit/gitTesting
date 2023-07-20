#include "client.hpp"

Client::Client()
{
}

void Client::connectToServer(const std::string& serverIP, unsigned short serverPort)
{
    socket.connect(serverIP, serverPort);
}

void Client::sendGameData(sf::Packet& packet)
{
    socket.send(packet);
}

void Client::receiveGameData(sf::Packet& packet)
{
    socket.receive(packet);
}

void Client::disconnect()
{
    socket.disconnect();
}

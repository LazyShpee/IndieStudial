#include "Peer.hpp"

using namespace rayzal;
#include <iostream>
Peer::Peer(unsigned int port, unsigned int maxConnections) : peer(RakNet::RakPeerInterface::GetInstance())
{
	this->peer->SetMaximumIncomingConnections(maxConnections);
	RakNet::SocketDescriptor *tmp = new RakNet::SocketDescriptor(port, 0);
	this->peer->Startup(maxConnections, tmp, 1);
	delete tmp;
}

Peer::Peer(std::string const & ip, unsigned int port) : peer(RakNet::RakPeerInterface::GetInstance())
{
	RakNet::SocketDescriptor *tmp = new RakNet::SocketDescriptor();
	this->peer->Startup(1, tmp, 1);
	delete tmp;
	this->peer->Connect(ip.c_str(), port, 0, 0);
}

Peer::~Peer()
{
	RakNet::RakPeerInterface::DestroyInstance(this->peer);
}

RakNet::RakPeerInterface * Peer::getPeer()
{
	return this->peer;
}

RakNet::Packet * Peer::receive()
{
	return this->peer->Receive();
}

void Peer::destroyPacket(RakNet::Packet * packet)
{
	if (packet)
		this->peer->DeallocatePacket(packet);
}

RakNet::SystemAddress Peer::getConnectedSystem(unsigned int id) const
{
	if (this->peer == NULL)
		return RakNet::SystemAddress();
	return this->peer->GetSystemAddressFromIndex(id);
}

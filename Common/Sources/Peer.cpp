#include "Peer.hpp"

using namespace rayzal;

Peer::Peer(unsigned int port, unsigned int maxConnections) : peer(RakNet::RakPeerInterface::GetInstance())
{
	this->peer->SetMaximumIncomingConnections(maxConnections);
	this->peer->Startup(maxConnections, &RakNet::SocketDescriptor(port, 0), 1);
}

Peer::Peer(std::string const & ip, unsigned int port) : peer(RakNet::RakPeerInterface::GetInstance())
{
	this->peer->Startup(1, &RakNet::SocketDescriptor(), 1);
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

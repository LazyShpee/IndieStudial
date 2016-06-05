#include "Constant.hpp"
#include "Peer.hpp"

Peer::Peer(unsigned int port)
{
	this->peer = RakNet::RakPeerInterface::GetInstance();
	if (port < 1024 || port > 65535)
		port = DEFAULT_SERVER_PORT;
	RakNet::SocketDescriptor sd(port, 0);
	this->peer->Startup(MAX_PLAYERS, &sd, 1);
	this->peer->SetMaximumIncomingConnections(MAX_PLAYERS);
	printf("Started server on port %d, accepting %d connections\n", port, MAX_PLAYERS);
}

Peer::~Peer()
{
	RakNet::RakPeerInterface::DestroyInstance(this->peer);
}

RakNet::RakPeerInterface * Peer::getPeer()
{
	return this->peer;
}

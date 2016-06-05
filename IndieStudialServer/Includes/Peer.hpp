#ifndef PEER_HPP_
# define PEER_HPP_

#include "Constant.hpp"

class Peer {
private:
	RakNet::RakPeerInterface* peer;

public:
	Peer(unsigned int port);
	~Peer();

	RakNet::RakPeerInterface* getPeer();
};

#endif
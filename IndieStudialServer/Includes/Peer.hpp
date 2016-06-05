#ifndef PEER_HPP_
# define PEER_HPP_

#include "TCPInterface.h"
#include "ConsoleServer.h"
#include "RakNetCommandParser.h"
#include "TelnetTransport.h"

#include "RakPeerInterface.h"
#include "LogCommandParser.h"
#include "GetTime.h"
#include "RakNetTransport2.h"
#include "LinuxStrings.h"
#include <stdio.h>
#include <string>

class Peer {
private:
	RakNet::RakPeerInterface* peer;

public:
	Peer(unsigned int port);
	~Peer();

	RakNet::RakPeerInterface* getPeer();
};

#endif
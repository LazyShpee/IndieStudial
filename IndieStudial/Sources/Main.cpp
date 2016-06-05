#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"
#include "StringCompressor.h"

using namespace std;

#define SERVER_PORT 12345
#define SERVER_ADDR "127.0.0.1"

RakNet::RakPeerInterface *peerInterface;
RakNet::Packet *packet;

int main(int argc, char* argv[])
{
	peerInterface = RakNet::RakPeerInterface::GetInstance();
	peerInterface->Startup(1, &RakNet::SocketDescriptor(), 1);

	printf("Client is connecting to %s:%d\n", SERVER_ADDR, SERVER_PORT);
	peerInterface->Connect(SERVER_ADDR, SERVER_PORT, 0, 0);

	// Handle messages
	while (true)
	{
		for (packet = peerInterface->Receive(); packet; peerInterface->DeallocatePacket(packet), packet = peerInterface->Receive())
		{
			switch (packet->data[0])
			{
			case ID_CONNECTION_REQUEST_ACCEPTED:
				printf("The connection to the server has been accepted.\n");
				break;
			}
		}
	}

	RakNet::RakPeerInterface::DestroyInstance(peerInterface);
	return 0;
}
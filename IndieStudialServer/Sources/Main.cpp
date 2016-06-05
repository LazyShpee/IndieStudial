
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"

#define SERVER_PORT 12345
#define MAX_CONNS 2000

int main(int argc, char* argv[])
{
	RakNet::RakPeerInterface *peerInterface = RakNet::RakPeerInterface::GetInstance();
	RakNet::Packet *packet;
	peerInterface->SetMaximumIncomingConnections(MAX_CONNS);
	peerInterface->Startup(MAX_CONNS, &RakNet::SocketDescriptor(SERVER_PORT, 0), 1);

	printf("Server is ready to receive connections.\n");

	// Handle messages
	while (true) {
		for (packet = peerInterface->Receive(); packet; peerInterface->DeallocatePacket(packet), packet = peerInterface->Receive())
		{
			switch (packet->data[0])
			{
			case ID_NEW_INCOMING_CONNECTION:
				printf("A remote system has successfully connected.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				printf("A remote system has disconnected.\n");
				break;
			case ID_CONNECTION_LOST:
				printf("A remote system lost the connection.\n");
				break;
			}
		}
	}

	RakNet::RakPeerInterface::DestroyInstance(peerInterface);

	return 0;
}
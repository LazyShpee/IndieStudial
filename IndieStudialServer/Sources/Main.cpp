
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"

#include <iostream>

#define SERVER_PORT 12345
#define MAX_CONNS 2000

RakNet::RakPeerInterface *peerInterface;

RakNet::SystemAddress getConnectedSystem(int index = 0);
void sendPacket(const RakNet::BitStream& bsOut, PacketReliability reliability = RELIABLE_ORDERED);

RakNet::SystemAddress getConnectedSystem(int index)
{
	if (peerInterface == NULL)
		return RakNet::SystemAddress();
	return peerInterface->GetSystemAddressFromIndex(index);
}

void sendPacket(const RakNet::BitStream& bsOut, PacketReliability reliability)
{
	peerInterface->Send(&bsOut, HIGH_PRIORITY, reliability, 0, getConnectedSystem(), false);
}

int main(int argc, char* argv[])
{
	peerInterface = RakNet::RakPeerInterface::GetInstance();
	RakNet::Packet *packet;
	peerInterface->SetMaximumIncomingConnections(MAX_CONNS);
	peerInterface->Startup(MAX_CONNS, &RakNet::SocketDescriptor(SERVER_PORT, 0), 1);

	printf("Server is ready to receive connections.\n");
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_USER_PACKET_ENUM + 1);
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
			default:
				printf("[%d]\n", packet->data[0]);
				break;
			}
		}
	}

	RakNet::RakPeerInterface::DestroyInstance(peerInterface);

	return 0;
}
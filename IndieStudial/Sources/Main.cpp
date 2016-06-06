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
	peerInterface->Startup(1, &RakNet::SocketDescriptor(), 1);
	printf("Client is connecting to %s:%d\n", SERVER_ADDR, SERVER_PORT);
	peerInterface->Connect(SERVER_ADDR, SERVER_PORT, 0, 0);
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_USER_PACKET_ENUM + 1);
	// Handle messages
	while (true)
	{
		for (packet = peerInterface->Receive(); packet; peerInterface->DeallocatePacket(packet), packet = peerInterface->Receive())
		{
			switch (packet->data[0])
			{
			case ID_CONNECTION_REQUEST_ACCEPTED:
				printf("The connection to the server has been accepted.\n");
				sendPacket(bsOut);
				break;
			}
			printf("[%d]\n", packet->data[0]);
		}
	}

	RakNet::RakPeerInterface::DestroyInstance(peerInterface);
	return 0;
}
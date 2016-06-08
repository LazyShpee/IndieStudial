
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "RakNetTypes.h"

#include "Peer.hpp"

#include <iostream>

#define SERVER_PORT 12345
#define MAX_CONNS 2000

//RakNet::RakPeerInterface *peerInterface;
//
//RakNet::SystemAddress getConnectedSystem(int index = 0);
//void sendPacket(const RakNet::BitStream& bsOut, PacketReliability reliability = RELIABLE_ORDERED);
//void sendPacket(const char *dat, size_t len, PacketReliability reliability = RELIABLE_ORDERED);


#pragma pack(push, 1)
struct my_packet {
	RakNet::MessageID	IdPacket;
	char				Data[20];
	char				Zero;
};

#pragma pack(pop)

//RakNet::SystemAddress getConnectedSystem(int index)
//{
//	if (peerInterface == NULL)
//		return RakNet::SystemAddress();
//	return peerInterface->GetSystemAddressFromIndex(index);
//}
//
//void sendPacket(const RakNet::BitStream& bsOut, PacketReliability reliability)
//{
//	peerInterface->Send(&bsOut, HIGH_PRIORITY, reliability, 0, getConnectedSystem(), false);
//}
//
//void sendPacket(const char *dat, size_t len, PacketReliability reliability)
//{
//	peerInterface->Send(dat, len, HIGH_PRIORITY, reliability, 0, getConnectedSystem(), false);
//}

int main(int argc, char* argv[])
{
	Peer peer;
	RakNet::Packet *packet;

	printf("Server is ready to receive connections.\n");

	my_packet *test;
	// Handle messages
	while (true) {
		for (packet = peer.receive(); packet; peer.destroyPacket(packet), packet = peer.receive())
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
			case ID_USER_PACKET_ENUM:
				test = (my_packet *)(packet->data);
				printf("Message : %s\n", test->Data);
				break;
			default:
				printf("[%d]\n", packet->data[0]);
				break;
			}
		}
	}
	return 0;
}
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"
#include "StringCompressor.h"
#include "Peer.hpp"
using namespace std;

#define SERVER_PORT 4242
#define SERVER_ADDR "127.0.0.1"

#pragma pack(push, 1)
typedef struct {
	RakNet::MessageID	IdPacket;
	char				Data[20];
	char				Zero;
} my_packet;
#pragma pack(pop)

int main(int argc, char *argv[])
{
	Peer peer(SERVER_ADDR, SERVER_PORT);
	RakNet::Packet *packet;
	printf("Client is connecting to %s:%d\n", SERVER_ADDR, SERVER_PORT);
	my_packet test = { ID_USER_PACKET_ENUM, "Vomi.", 0 };
	// Handle messages
	while (true)
	{
		for (packet = peer.receive(); packet; peer.destroyPacket(packet), packet = peer.receive())
		{
			switch (packet->data[0])
			{
			case ID_CONNECTION_REQUEST_ACCEPTED:
				printf("The connection to the server has been accepted.\n");
				peer.sendPacket(&test);
				break;
			}
			printf("[%d]\n", packet->data[0]);
		}
	}

	return 0;
}
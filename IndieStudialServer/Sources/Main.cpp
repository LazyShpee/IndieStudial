#include "Peer.hpp"
#include "Constant.hpp"

void initServer(const std::string& portString)
{
	;
}

int main(int c, char *v[]) {
	Peer p(1234);
	RakNet::Packet *packet;
	while (1) {
		printf("Receiving packets\n");
		for (packet = p.getPeer()->Receive(); packet; p.getPeer()->DeallocatePacket(packet), packet = p.getPeer()->Receive())
		{
			printf("%s\n", packet->data);
		}
		SLEEP(1000);
	}
}
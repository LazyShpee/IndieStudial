#ifndef PEER_HPP_
# define PEER_HPP_

# include "IncludeRakNet.hpp"
# include <string>

namespace rayzal
{
  class Peer {
  private:
    RakNet::RakPeerInterface* peer;

  public:
    Peer(unsigned int port = 4242, unsigned int maxConnections = 4);
    Peer(std::string const &ip, unsigned int port = 4242);
    ~Peer();

    RakNet::RakPeerInterface* getPeer();

    RakNet::Packet *receive();
    void destroyPacket(RakNet::Packet *packet);

    RakNet::SystemAddress getConnectedSystem(unsigned int id = 0) const;
	template<class T>
	void sendPacket(T* packetStruct, unsigned int clientID = 0, PacketReliability reliability = RELIABLE_ORDERED)
	{
		this->peer->Send((char *)packetStruct, sizeof(*packetStruct), HIGH_PRIORITY, reliability, 0, getConnectedSystem(clientID), false);
	}
	template<class T>
	void sendPacket(T* packetStruct, RakNet::SystemAddress const & addr, PacketReliability reliability = RELIABLE_ORDERED)
	{
		this->peer->Send((char *)packetStruct, sizeof(*packetStruct), HIGH_PRIORITY, reliability, 0, addr, false);
	}
  };
}

#endif

#include "Rayzal.hpp"
#include "Instance.hpp"

std::mutex rayzal::ListenerThread::mutex;

rayzal::ListenerThread::ListenerThread(rayzal::Peer *peer)
  : _peer(peer)
{
  this->_thread = new std::thread(this->loop);
}

rayzal::ListenerThread::~ListenerThread(void)
{
  this->_thread.join();
  delete this->_thread;
}

void rayzal::ListenerThread::loop(void)
{
  RakNet::Packet *packet;
  while((packet = this->_peer->receive()))
    {
      switch (packet->data[0])
	{
	  // INSEREZ ICI LE CODE QUI VA GERER LES ENTITIES
	case CHAATE:
	  CHÂÂÂÂÂTTE;
	default:
	  omg;
	}
      this->_peer->destroyPacket();
    }
  return (NULL);
}

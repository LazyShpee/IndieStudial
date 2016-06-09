#include "Rayzal.hpp"
#include "Loop.hpp"

std::mutex rayzal::ListenerThread::mutex;

rayzal::ListenerThread::ListenerThread(iscene::ISceneManager *smgr,
				       rayzal::Peer *peer)
  : _smgr(smgr), _peer(peer)
{
  this->_thread = new std::thread(this->loop);
}

rayzal::ListenerThread::~ListenerThread(void)
{
  this->_thread->join();
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
	case :
	  ;
	default:
	  ;
	}
      this->_peer->destroyPacket();
    }
  return (NULL);
}

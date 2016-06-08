#include "Rayzal.cpp"

pthread_mutex_t rayzal::ListenerThread::mutex;

rayzal::ListenerThread::ListenerThread(iscene::ISceneManager *smgr,
				       rayzal::Peer *peer)
  : _set(true), _smgr(smgr), _peer(peer)
{
}

rayzal::ListenerThread::~ListenerThread(void)
{
  if (this->_set)
    pthread_join(this->_thread_id, NULL);
}

bool rayzal::ListenerThread::start(void)
{
  this->_set = !pthread_create(&this->_thread_id, NULL, &this->loop, NULL);
  return (this->_set);
}

void *rayzal::ListenerThread::loop(void *)
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

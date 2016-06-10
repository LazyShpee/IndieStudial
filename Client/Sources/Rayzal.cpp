#include "Rayzal.hpp"
#include "Loop.hpp"

std::mutex rayzal::ListenerThread::mutex;

rayzal::ListenerThread::ListenerThread(iscene::ISceneManager *smgr,
				       rayzal::Peer *peer)
  : _thread(new std::thread(this->loop)), _smgr(smgr), _peer(peer), _wait(OK_CODE)
{
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
	case ID_CONNECTION_REQUEST_ACCEPTED:
	  std::cout << "The connection request has been accepted." << std::endl;
	  break;
	case ID_NO_FREE_INCOMING_CONNECTIONS:
	  std::cout << "No more free connections avalaible in server." << std::endl;
	  rayzal::ListenerThread::mutex.lock();
	  this->_wait = ERROR_CODE;
	  rayzal::ListenerThread::mutex.unlock();
	  break;
	case ID_CONNECTION_LOST:
	  std::cout << "Connection lost." << std::endl;
	  rayzal::ListenerThread::mutex.lock();
	  this->_wait = ERROR_CODE;
	  rayzal::ListenerThread::mutex.unlock();
	  break;
	case ID_ENTER_GAME:
	  rayzal::ListenerThread::mutex.lock();
	  this->_wait = OK_CONNECTION;
	  rayzal::ListenerThread::mutex.unlock();
	  break;
	case ID_GAME_INFOS:
	  // ADD rayzal::GameInfoPacket INFOS TO ...........  IDK MAYBE A GETTER/SETTER WILL BE ADDED TO THE class core::GameLoop ah non j'ai menti on va juste fill this->_player_uuid_list et this->_player_nick_list ah non j'ai encore menti omg
	  break;
	case ID_ENTITY:
	  // ADD rayzal::EntityPacket INFOS TO core::EntityList
	  break;
	case ID_DELETE:
	  // LOOK FOR ENTITY IN core::EntityList AND DELETE IT
	  break;
	default:
	  std::cout << "[" << packet->data[0] << "]" << std::endl;
	  break;
	}
      this->_peer->destroyPacket();
    }
  return (NULL);
}

int rayzal::ListenerThread::wait_connection(void) const
{
  return (this->_wait);
}

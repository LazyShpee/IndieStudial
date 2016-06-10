#include "Constants.hpp"
#include "Loop.hpp"
#include "Rayzal.hpp"
#include <iostream>

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
  rayzal::BasicPacket *basicPacket;
  rayzal::EntityPacket *entPacket;
  std::vector<Entity *>::iterator entIt;
  bool foundEnt;
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
		core::gameInfo = *((rayzal::GameInfoPacket *)packet);
	  // COPY rayzal::GameInfoPacket INFOS TO THE core::gameInfo VARIABLE
	  break;
	case ID_ENTITY:
		entPacket = (rayzal::EntityPacket *)packet;
		entIt = core::EntityList.begin();
		foundEnt = false;
		while (entIt != core::EntityList.end()) {
			if ((*entIt)->getUUID == entPacket->uuid) {
				(*entIt)->applyPacket(entPacket);
				foundEnt = true;
				break;
			}
			entIt++;
		}
		if (!foundEnt)
			new Entity(entPacket, this->_smgr);
	  // ADD rayzal::EntityPacket INFOS TO core::EntityList
	  break;
	case ID_DELETE:
		basicPacket = (rayzal::BasicPacket *)packet;
		entIt = core::EntityList.begin();
		while (entIt != core::EntityList.end()) {
			if ((*entIt)->getUUID == entPacket->uuid) {
				(*entIt)->applyPacket(basicPacket);
				break;
			}
			entIt++;
		}
		break;
	default:
	  std::cout << "[" << packet->data[0] << "]" << std::endl;
	  break;
	}
      this->_peer->destroyPacket(packet);
    }
  return;
}

int rayzal::ListenerThread::wait_connection(void) const
{
  return (this->_wait);
}

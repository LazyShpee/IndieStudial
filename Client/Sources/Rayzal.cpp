#include <functional>
#include <iostream>

#include "Constants.hpp"
#include "IncludeIrrlicht.hpp"
#include "Rayzal.hpp"
#include "Entity.hpp"
#include "Loop.hpp"

std::mutex rayzal::ListenerThread::mutex;

rayzal::ListenerThread::ListenerThread(iscene::ISceneManager *smgr,
				       rayzal::Peer *peer)
  : _smgr(smgr), _peer(peer), _wait(OK_CODE)
{
  this->_thread = new std::thread(&rayzal::ListenerThread::loop, this);
  // INSERER ICI LE CODE QUI VA INITIALISER LE SON OMG
}

rayzal::ListenerThread::~ListenerThread(void)
{
  // INSERER ICI LE CODE QUI VA UNINITIALIZE LE SON OMG
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
	  core::selfInfo.PacketType = ID_PLAYER_INFOS;
	  memcpy(core::selfInfo.nick, "OMGPLAYER", 10);
	  core::selfInfo.uuid = 0;
	  this->_peer->sendPacket(&(core::selfInfo), 0);
	  this->_wait = OK_CONNECTION;
	  rayzal::ListenerThread::mutex.unlock();
	  break;
	case ID_PLAYER_INFOS:
		core::selfInfo = *((rayzal::PlayerInfoPacket*)packet);
		break;
	case ID_GAME_INFOS:
		core::gameInfo = *((rayzal::GameInfoPacket *)packet);
	  break;
	case ID_ENTITY:
		entPacket = (rayzal::EntityPacket *)packet;
		entIt = core::EntityList.begin();
		foundEnt = false;
		while (entIt != core::EntityList.end()) {
		  if ((*entIt)->getUUID() == entPacket->uuid) {
				(*entIt)->applyPacket(entPacket);
				foundEnt = true;
				break;
			}
			entIt++;
		}
		if (!foundEnt)
			new Entity(entPacket, this->_smgr);
	  break;
	case ID_DELETE:
		basicPacket = (rayzal::BasicPacket *)packet;
		entIt = core::EntityList.begin();
		while (entIt != core::EntityList.end()) {
		  if ((*entIt)->getUUID() == basicPacket->uuid) {
				(*entIt)->applyPacket(basicPacket);
				break;
			}
			entIt++;
		}
		break;
	case ID_SOUND:
	  // INSERER ICI LE CODE QUI VA LIRE LE SON DECRIT DANS rayzal::SoundPacket
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

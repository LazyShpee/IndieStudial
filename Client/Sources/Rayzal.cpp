#include <iostream>
#include <fstream>
#include <functional>

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
  while (this->wait_connection() != ERROR_CODE)
    if ((packet = this->_peer->receive()))
      {
	rayzal::ListenerThread::mutex.lock();
	switch (packet->data[0])
	  {
	  case ID_CONNECTION_REQUEST_ACCEPTED:
	    std::cout << "The connection request has been accepted." << std::endl;
	    this->_wait = OK_CONNECTION;
	    break;
	  case ID_NO_FREE_INCOMING_CONNECTIONS:
	    std::cout << "No more free connections avalaible in server." << std::endl;
	    this->_wait = ERROR_CODE;
	    break;
	  case ID_CONNECTION_LOST:
	    std::cout << "Connection lost." << std::endl;
	    this->_wait = ERROR_CODE;
	    break;
	  case ID_ENTER_GAME:
	    std::cout << "OMG On entre dans la game." << std::endl;
	    core::selfInfo.PacketType = ID_PLAYER_INFOS;
	    memcpy(core::selfInfo.nick, "OMGPLAYER", 10);
	    core::selfInfo.uuid = 0;
	    this->_peer->sendPacket(&(core::selfInfo), 0);
	    this->_wait = OK_CONNECTION;
	    break;
	  case ID_PLAYER_INFOS:
	    std::cout << "Quelques infos sur le player." << std::endl;
	    core::selfInfo = *((rayzal::PlayerInfoPacket*)packet);
	    break;
	  case ID_GAME_INFOS:
	    std::cout << "Quelques infos sur la game." << std::endl;
	    core::gameInfo = *((rayzal::GameInfoPacket *)packet);
	    break;
	  case ID_ENTITY:
	    std::cout << "OOOOMG une entité." << std::endl;
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
	rayzal::ListenerThread::mutex.unlock();
	this->_peer->destroyPacket(packet);
      }
  return;
}

int rayzal::ListenerThread::wait_connection(void) const
{
  int ret;

  rayzal::ListenerThread::mutex.lock();
  ret = this->_wait;
  rayzal::ListenerThread::mutex.unlock();
  return (ret);
}

void rayzal::ListenerThread::join(void)
{
  std::ofstream outfile ("done");
  outfile << "#JeSuisLegit" << std::endl;
  outfile.close();
  rayzal::ListenerThread::mutex.lock();
  this->_wait = ERROR_CODE;
  rayzal::ListenerThread::mutex.unlock();
}

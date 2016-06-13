#include <iostream>
#include <fstream>
#include <functional>

#include "Constants.hpp"
#include "IncludeIrrlicht.hpp"
#include "Rayzal.hpp"
#include "Entity.hpp"
#include "Loop.hpp"
#include "Sound.hpp"

std::mutex rayzal::ListenerThread::mutex;

rayzal::ListenerThread::ListenerThread(iscene::ISceneManager *smgr,
				       rayzal::Peer *peer)
  : _peer(peer), _smgr(smgr), _wait(OK_CODE)
{
  this->_thread = new std::thread(&rayzal::ListenerThread::loop, this);
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
  rayzal::SoundPacket *sndPacket;
  std::vector<Entity *>::iterator entIt;
  bool foundEnt;
  int i;

  irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
  soundNode = new CIrrKlangSceneNode(soundEngine, _smgr->getRootSceneNode(), _smgr, 666);
  soundNode->setSoundFileName(SoundDescription[1].soundPath);
  soundNode->setMinMaxSoundDistance(30.0f);
  soundNode->setLoopingStreamMode();

  while (this->wait_connection() != ERROR_CODE)
    if ((packet = this->_peer->receive()))
      {
	rayzal::ListenerThread::mutex.lock();
	switch (packet->data[0])
	  {
	  case ID_CONNECTION_REQUEST_ACCEPTED:
	    std::cout << core::getSelfInfo()->nick << ": The connection request has been accepted." << std::endl;
	    core::getSelfInfo()->PacketType = rayzal::ID_PLAYER_INFOS;
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
	    core::getSelfInfo()->PacketType = rayzal::ID_PLAYER_INFOS;
	    core::getSelfInfo()->uuid = 0;
	    this->_peer->sendPacket(core::getSelfInfo());
	    this->_wait = OK_CONNECTION;
	    break;

	  case ID_PLAYER_INFOS:
	    memcpy(core::getSelfInfo(), packet->data, sizeof(rayzal::PlayerInfoPacket));
	    std::cout << "Quelques infos sur le player: " << core::getSelfInfo()->uuid << std::endl;
	    this->_wait = OK_CONNECTION;
	    break;
	  case ID_GAME_INFOS:
	    std::cout << "Quelques infos sur la game." << std::endl;
	    memcpy(core::getGameInfo(), packet->data, sizeof(rayzal::GameInfoPacket));
	    break;

	  case ID_ENTITY:
	    entPacket = (rayzal::EntityPacket *)packet->data;
		//std::cout << "OOOOMG une entité.:" << entPacket->EntityType << std::endl;
	    entIt = core::getEntitylist().begin();
	    foundEnt = false;
	    while (entIt != core::getEntitylist().end()) {
			if ((*entIt)->getUUID() == entPacket->uuid) {
				(*entIt)->applyPacket(entPacket);
				foundEnt = true;
				break;
			}
	      entIt++;
	    }
		if (!foundEnt)
		{
			std::cout << "lololole" << std::endl;
			new Entity(entPacket, this->_smgr);
		}
	    break;
	  case ID_DELETE:
	    basicPacket = (rayzal::BasicPacket *)packet->data;
	    entIt = core::getEntitylist().begin();
	    while (entIt != core::getEntitylist().end()) {
	      if ((*entIt)->getUUID() == basicPacket->uuid) {
		(*entIt)->applyPacket(basicPacket);
		break;
	      }
	      entIt++;
	    }
	    break;
	  case ID_SOUND:
		  sndPacket = (rayzal::SoundPacket *)packet->data;
		  for (i = 0; SoundDescription[i].soundPath != 0 && SoundDescription[i].type != sndPacket->sound_id; i++);
		  if (SoundDescription[i].soundPath != 0)
		  {
			  soundNode->setSoundFileName(SoundDescription[i].soundPath);
			  soundNode->setMinMaxSoundDistance(300.0f);
			  if (sndPacket->loop)
				  soundNode->setLoopingStreamMode();
			  else
				  soundNode->setPlayOnceMode();
		  }
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

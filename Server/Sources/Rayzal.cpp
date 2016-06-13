#include "Instance.hpp"
#include "Rayzal.hpp"
#include "Constants.hpp"
#include "Player.hpp"
#include "ConfigSelector.hpp"

#include <sstream>
#include <iostream>

std::mutex rayzal::ListenerThread::mutex;

rayzal::ListenerThread::ListenerThread(rayzal::Peer *peer, irr::scene::ISceneManager *smgr)
  : _peer(peer), _smgr(smgr)
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
  std::cout << "OMG un packet." << std::endl;
  RakNet::Packet *packet;
  rayzal::InputPacket *inputPacket;
  rayzal::PlayerInfoPacket *playerInfo;
  rayzal::BasicPacket bPacket;
  std::vector<Player *>::const_iterator plIt;
  Player *pl;
  int rd;
  ConfigSelector::Config conf;

  while (42)
    if ((packet = this->_peer->receive()))
      {
	rayzal::ListenerThread::mutex.lock();
	switch (packet->data[0])
	  {
	  case ID_NEW_INCOMING_CONNECTION:
	    std::cout << "A remote system has successfully connected." << std::endl;
		bPacket.PacketType = ID_ENTER_GAME;
		this->_peer->sendPacket(&bPacket, packet->systemAddress);
		break;
	  case ID_DISCONNECTION_NOTIFICATION:
	    std::cout << "A remote system has disconnected." << std::endl;
	    break;
	  case ID_CONNECTION_LOST:
	    std::cout << "A remote system lost the connection." << std::endl;
	    break;
	  case ID_ENTER_QUEUE:
	    std::cout << "OMG un pédé." << std::endl;
	    break;
	  case ID_PLAYER_INFOS:
	    playerInfo = (rayzal::PlayerInfoPacket*)(packet->data);
	    playerInfo->uuid = core::UUID();
	    std::cout << "Quelques infos sur le player:" << playerInfo->uuid << std::endl;
	    rd = rand() % 5 + 1;
	    playerInfo->car_model = 39 + rd; // SHOULD BE RANDOM
	    pl = new Player(playerInfo->uuid, playerInfo->car_model, this->_smgr);
	    core::Instance::PlayerList.push_back(pl);
	    pl->setConfig(Vehicle::getDefaultConfig());
	    memcpy(playerInfo->car_desc, conf.car_desc.c_str(), conf.car_desc.length());
	    memcpy(playerInfo->car_name, conf.car_name.c_str(), conf.car_name.length());
	    conf = ConfigSelector::getConfigFromIni(std::string("conf") + static_cast<std::ostringstream*>(&(std::ostringstream() << rd))->str() + std::string(".ini"));
	    this->_peer->sendPacket(playerInfo, packet->systemAddress);
	    break;

	  case ID_INPUT:
	    inputPacket = (rayzal::InputPacket*)(packet->data);
	    if (inputPacket->input)
	      std::cout << "ET BIIIM, DES INPUTS from: " << inputPacket->uuid << std::endl;
	    plIt = core::Instance::PlayerList.begin();
	    while (plIt != core::Instance::PlayerList.end()) {
	      if (inputPacket->uuid == (*plIt)->getEntity()->getUUID()) {
		(*plIt)->setInput(inputPacket->input);
		break;
	      }
	      plIt++;
	    }
	    break;
	  default:
	    std::cout << "[" << packet->data[0] << "]" << std::endl;
	    break;
	  }
	// std::cout << ">>>>> OMG: " << core::Instance::PlayerList.size() << " <<<<<<<<<" << std::endl;
	rayzal::ListenerThread::mutex.unlock();
	this->_peer->destroyPacket(packet);
      }
  return;
}

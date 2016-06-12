#include "Instance.hpp"
#include "Rayzal.hpp"
#include "Constants.hpp"
#include "Player.hpp"
#include <iostream>

std::mutex rayzal::ListenerThread::mutex;

rayzal::ListenerThread::ListenerThread(rayzal::Peer *peer)
  : _peer(peer)
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
  std::vector<Player *>::const_iterator plIt;
  while (42)
    if ((packet = this->_peer->receive()))
      {
	rayzal::ListenerThread::mutex.lock();
	switch (packet->data[0])
	  {
	  case ID_NEW_INCOMING_CONNECTION:
	    std::cout << "A remote system has successfully connected." << std::endl;
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
	    std::cout << "Quelques infos sur le player." << std::endl;
	    playerInfo = (rayzal::PlayerInfoPacket*)(packet->data);
	    playerInfo->nick[SHORT_BUFFER] = 0;
	    playerInfo->uuid = core::UUID();
	    core::Instance::PlayerList.push_back(new Player(playerInfo->uuid, this->_smgr));
	    this->_peer->sendPacket(playerInfo, packet->systemAddress);
	    break;
	  case ID_INPUT:
	    std::cout << "ET BIIIM, DES INPUTS" << std::endl;
	    inputPacket = (rayzal::InputPacket*)(packet->data);
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
	rayzal::ListenerThread::mutex.unlock();
	this->_peer->destroyPacket(packet);
      }
  return;
}

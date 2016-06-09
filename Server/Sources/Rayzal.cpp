#include "Rayzal.hpp"
#include "Instance.hpp"
#include "Constants.hpp"
#include "Player.hpp"
#include <iostream>

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
  rayzal::InputPacket *inputPacket;
  rayzal::PlayerInfoPacket *playerInfo;
  std::vector<Player *>::const_iterator plIt;
  while((packet = this->_peer->receive()))
    {
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
	  rayzal::ListenerThread::mutex.lock();
	  this->_queue++;
	  rayzal::ListenerThread::mutex.unlock();
	  break;
	case ID_PLAYER_INFOS:
	  // CREATE PLAYER ENTITY INTO core::Instance::PlayerList (push_back(new ...))
		playerInfo = (rayzal::PlayerInfoPacket*)(packet->data);
		playerInfo->nick[32] = 0;
		playerInfo->uuid = core::UUID();
		core::Instance::PlayerList.push_back(new Player(playerInfo->uuid, "player", this->_smgr));
		this->_peer->sendPacket(playerInfo, packet->systemAddress);
	  break;
	case ID_INPUT:
	  rayzal::ListenerThread::mutex.lock();
	  // SET THE NEW VALUE OF INPUT FOR THE PLAYER (iterate through PlayerList and .setInput()
	  inputPacket = (rayzal::InputPacket*)(packet->data);
	  plIt = core::Instance::PlayerList.begin();
	  while (plIt != core::Instance::PlayerList.end()) {
		  if (inputPacket->uuid == (*plIt)->getEntity()->getUUID()) {
			  (*plIt)->setInput(inputPacket->input);
			  break;
		  }
		  plIt++;
	  }
	  rayzal::ListenerThread::mutex.unlock();
	  break;
	default:
	  std::cout << "[" << packet->data[0] << "]" << std::endl;
	  break;
	}
      this->_peer->destroyPacket(packet);
    }
  return;
}

bool rayzal::ListenerThread::getQueue(void) const
{
  rayzal::ListenerThread::mutex.lock();
  bool ret = this->_queue < NB_PLAYERS;
  rayzal::ListenerThread::mutex.unlock();
  return (!ret);
}

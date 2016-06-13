#include "Instance.hpp"
#include "Constants.hpp"

std::vector<Player *> core::Instance::PlayerList;
std::vector<irr::u32> core::Instance::ToDelteQueue;

core::Instance::Instance(core::device_t *device, rayzal::Peer *peer)
  : _device(device), _peer(peer)
{
}

bool core::Instance::init(void)
{
  iscene::IAnimatedMesh *map = this->_device->smgr->getMesh(MAP_MESH_PATH);
  iscene::IMeshSceneNode *map_node = 0;

  if (map)
    {
      map_node = this->_device->smgr->addOctreeSceneNode(map->getMesh(0), 0, -1, 1024);
      if (map_node)
	{
	  map_node->setPosition(icore::vector3df(150, 0, 100));
	  map_node->setScale(icore::vector3df(10.0f, 10.0f, 10.0f));
	}
    }
  // INSERER ICI LA LOADATION DES MESH ET DES COLLISIONS
  this->_before = this->_device->ptr->getTimer()->getTime();
  return (OK_CODE);
}

#include <iostream>

int core::Instance::loop(void)
{
  const irr::u32 now = this->_device->ptr->getTimer()->getTime();
  const irr::f32 dt = (irr::f32)(now - this->_before) / 1000.f;
  this->_before = now;
  rayzal::ListenerThread::mutex.lock();

  std::vector<Player*>::const_iterator it_player = core::Instance::PlayerList.cbegin();
  while (it_player != core::Instance::PlayerList.cend())
  {
    (*it_player)->update(dt, this->_device->smgr);
	  it_player++;
  }
  RakNet::SystemAddress addr[42];
  unsigned short conn, i;
  std::vector<Entity *>::const_iterator it = core::getEntitylist().cbegin();
  rayzal::EntityPacket *ent;
  while (it != core::getEntitylist().cend()) {
    i = 0;
	conn = 42;
	ent = (*it)->getPacket();
	this->_peer->getPeer()->GetConnectionList(addr, &conn);
	while (i < conn) {
		ent->EntityType = rayzal::ID_ENTITY;
      this->_peer->sendPacket(ent, addr[i]);
      i++;
    }
	delete ent;
    it++;
  }

  rayzal::ListenerThread::mutex.unlock();

  return (OK_CODE);
}

irr::u32 core::UUID() {
  std::vector<Entity *>::const_iterator it = core::getEntitylist().begin();
	irr::u32 uuid = 0;
	while (uuid == 0) {
		uuid = (irr::u32)rand();
		while (it != core::getEntitylist().end()) {
			if ((*it)->getUUID() == uuid) {
				uuid = 0;
				break;
			}
		}
	}
	return uuid;
}

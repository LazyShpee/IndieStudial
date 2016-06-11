#include "Instance.hpp"
#include "Constants.hpp"

std::vector<Player *> core::Instance::PlayerList;

core::Instance::Instance(core::device_t *device, rayzal::Peer *peer)
  : _device(device), _peer(peer)
{
}

bool core::Instance::init(void)
{
  // INSERER ICI LA LOADATION DES MESH ET DES COLLISIONS
  this->_before = this->_device->ptr->getTimer()->getTime();
  return (OK_CODE);
}

int core::Instance::loop(void)
{
  const irr::u32 now = this->_device->ptr->getTimer()->getTime();
  // const irr::f32 dt = (irr::f32)(now - this->_before) / 1000.f;
  this->_before = now;

  // INSERER ICI LE CODE QUI VA ITERATE DANS core::Instance::PlayerList et faire .update(dt)

  RakNet::SystemAddress *addr = NULL;
  unsigned short conn, i;
  this->_peer->getPeer()->GetConnectionList(addr, &conn);
  std::vector<Entity *>::const_iterator it = core::EntityList.cbegin();
  const rayzal::EntityPacket *ent;
  while (it != core::EntityList.cend()) {
    i = 0;
    while (i < conn) {
      ent = (*it)->getPacket();
      this->_peer->sendPacket(ent, addr[i]);
      i++;
    }
    it++;
  }

  core::EntityList.cbegin();

  return (OK_CODE);
}

irr::u32 core::UUID() {
	std::vector<Entity *>::const_iterator it = core::EntityList.begin();
	irr::u32 uuid = 0;
	while (uuid == 0) {
		uuid = (irr::u32)rand();
		while (it != core::EntityList.end()) {
			if ((*it)->getUUID() == uuid) {
				uuid = 0;
				break;
			}
		}
	}
	return uuid;
}

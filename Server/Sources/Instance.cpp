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
  // INSERER ICI L'INIT DE LA CLOCK
  return (OK_CODE);
}

int core::Instance::loop(void)
{
  // INSERER ICI LE CODE QUI VA UPDATE LA CLOCK
  // INSERER ICI LE CODE QUI VA UPDATE LES ENTITES ET LES ENVOYER PAR this->_peer
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

#include "IncludeIrrlicht.hpp"
#include "Entity.hpp"
#include <iostream>

// Entity::Entity(std::string const & meshPath, std::string const & name, iscene::ISceneManager *smgr) {
// 	this->mesh = smgr->getMesh(meshPath.c_str());
// 	this->node = smgr->addAnimatedMeshSceneNode(this->mesh);
// 	this->node->setName(name.c_str());
// 	this->smgr = smgr;
// 	std::cout << "OMG UNE NOUVELLE ENTITY" << std::endl;
// }

Entity::Entity(unsigned char type, unsigned int uuid, iscene::ISceneManager * smgr)
  : type(type), uuid(uuid), smgr(smgr)
{
	size_t i = 0;
	while (EntityDescription[i].meshPath) {
		if (EntityDescription[i].type == type)
			break;
		i++;
	}
	if (!EntityDescription[i].meshPath)
		i = 0;
	this->mesh = smgr->getMesh(EntityDescription[i].meshPath);
	this->node = smgr->addAnimatedMeshSceneNode(this->mesh);
	this->node->setPosition(icore::vector3df(-600, 0, 100));
	this->node->setScale(icore::vector3df(2.0f, 2.0f, 2.0f));
	this->node->setMaterialFlag(ivideo::EMF_LIGHTING, false);
	core::getEntitylist().push_back(this);
	std::cout << "construct 1" << std::endl;
	//std::cout << "OMG UNE NOUVELLE ENTITY" << std::endl;
}




Entity::Entity(rayzal::EntityPacket const *packet, iscene::ISceneManager * smgr)
  : type(packet->EntityType), uuid(packet->uuid), smgr(smgr)
{
	size_t i = 0;
	while (EntityDescription[i].meshPath) {
		if (EntityDescription[i].type == packet->EntityType)
			break;
		i++;
	}
	if (!EntityDescription[i].meshPath)
		i = 0;
	this->mesh = smgr->getMesh(EntityDescription[i].meshPath);
	this->node = smgr->addAnimatedMeshSceneNode(this->mesh);
	this->node->setPosition(icore::vector3df(-500, 0, 100));
	this->node->setScale(icore::vector3df(2.0f, 2.0f, 2.0f));
	this->node->setMaterialFlag(ivideo::EMF_LIGHTING, false);
	core::getEntitylist().push_back(this);

	std::cout << "construct 2" << std::endl;
}

Entity::~Entity() {
  std::vector<Entity *>::iterator it = core::getEntitylist().begin();
  while (it != core::getEntitylist().end()) {
		if (*it == this) {
		  core::getEntitylist().erase(it);
			break;
		}
		++it;
	}
}

iscene::IAnimatedMesh						*Entity::getMesh() const {
	return (this->mesh);
}

iscene::IAnimatedMeshSceneNode				*Entity::getNode() const {
	return (this->node);
}

void										Entity::addWorldCollision(iscene::ISceneNodeAnimatorCollisionResponse *anim)
{
	this->worldCollision.push_back(anim);
}

std::vector<iscene::ISceneNodeAnimatorCollisionResponse*> Entity::getWorldCollision() const {
	return (this->worldCollision);
}

rayzal::EntityPacket * Entity::getPacket(void) const
{
	rayzal::EntityPacket *packet = new rayzal::EntityPacket;
	icore::vector3df pos = this->node->getPosition();
	icore::vector3df rot = this->node->getRotation();
	packet->EntityType = this->type;
	packet->PacketType = rayzal::ID_ENTITY;
	packet->uuid = this->uuid;

	packet->px = pos.X;
	packet->py = pos.Y;
	packet->pz = pos.Z;
	packet->rx = rot.X;
	packet->ry = rot.Y;
	packet->rz = rot.Z;
	return (packet);
}

void Entity::applyPacket(rayzal::EntityPacket const * packet)
{
	icore::vector3df pos(packet->px, packet->py, packet->pz);
	icore::vector3df rot(packet->rx, packet->ry, packet->rz);
	this->node->setPosition(pos);
	this->node->setRotation(rot);
}

void Entity::applyPacket(rayzal::BasicPacket const * packet)
{
	if (packet->uuid == this->uuid && packet->PacketType == rayzal::ID_DELETE) {
		delete this;
	}
}

irr::u32 Entity::getUUID() {
	return this->uuid;
}

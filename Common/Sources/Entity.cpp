#include "IncludeIrrlicht.hpp"

Entity::Entity(std::string const & meshPath, std::string const & name, iscene::ISceneManager *smgr) {
	this->mesh = smgr->getMesh(meshPath.c_str());
	this->node = smgr->addAnimatedMeshSceneNode(this->mesh);
	this->node->setName(name.c_str());
	this->smgr = smgr;
}

Entity::Entity(unsigned char type, unsigned int uuid, iscene::ISceneManager * smgr)
  : type(type), uuid(uuid), smgr(smgr)
{
	size_t i = 0;
	while (EntityDescription[i].meshPath) {
		if (EntityDescription[i].type == type)
			break;
		i++;
	}
	this->mesh = smgr->getMesh(EntityDescription[i].meshPath);
	this->node = smgr->addAnimatedMeshSceneNode(this->mesh);
	core::EntityList.push_back(this);
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
	this->mesh = smgr->getMesh(EntityDescription[i].meshPath);
	this->node = smgr->addAnimatedMeshSceneNode(this->mesh);
	core::EntityList.push_back(this);
}

Entity::~Entity() {
	std::vector<Entity *>::iterator it = core::EntityList.begin();
	while (it != core::EntityList.end()) {
		if (*it == this) {
			core::EntityList.erase(it);
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

rayzal::EntityPacket const * Entity::getPacket(void) const
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
	if (packet->uuid != this->uuid)
		return;
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

void Entity::updateEntity(rayzal::EntityPacket const *packet)
{
	if (packet->uuid != this->uuid)
		return;
	icore::vector3df pos(packet->px, packet->py, packet->pz);
	icore::vector3df rot(packet->rx, packet->ry, packet->rz);
	this->node->setPosition(pos);
	this->node->setRotation(rot);
}

irr::u32 Entity::getUUID() {
	return this->uuid;
}

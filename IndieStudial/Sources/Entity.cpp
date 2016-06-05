#include "Entity.hpp"

Entity::Entity(std::string const & meshPath, std::string const & name, iscene::ISceneManager *smgr) {
	this->mesh = smgr->getMesh(meshPath.c_str());
	this->node = smgr->addAnimatedMeshSceneNode(this->mesh);
	this->node->setName(name.c_str());
	this->smgr = smgr;
}

iscene::IAnimatedMesh						*Entity::getMesh() const {
	return (this->mesh);
}

iscene::IAnimatedMeshSceneNode				*Entity::getNode() const {
	return (this->node);
}

/*void										Entity::setWorldCollision(std::vector<iscene::ISceneNodeAnimatorCollisionResponse*> worldCollision) {
	this->worldCollision = worldCollision;
}*/

void										Entity::addWorldCollision(iscene::ISceneNodeAnimatorCollisionResponse *anim)
{
	this->worldCollision.push_back(anim);
}

std::vector<iscene::ISceneNodeAnimatorCollisionResponse*> Entity::getWorldCollision() const {
	return (this->worldCollision);
}

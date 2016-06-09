#include "Missile.hpp"

Missile::Missile(iscene::ISceneNode *player, iscene::ISceneManager *smgr) : entity(new Entity(std::string(MISSILE_MESH_PATH), std::string("missile"), smgr))
{
	this->entity->getNode()->setPosition(icore::vector3df(player->getPosition().X, player->getPosition().Y + 20.f, player->getPosition().Z));
	this->entity->getNode()->setRotation(player->getRotation());

	iscene::IMetaTriangleSelector*			meta = smgr->createMetaTriangleSelector(); // Hold several triangles at a time
	iscene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
		meta, this->entity->getNode(), this->entity->getNode()->getTransformedBoundingBox().getExtent(),
		icore::vector3df(sin(player->getRotation().Y / 180.f * M_PI + M_PI_2) * 10.f, 0, cos(player->getRotation().Y / 180.f * M_PI + M_PI_2) * 10.f));

	meta->drop();
	this->entity->getNode()->addAnimator(anim);
	anim->drop();
}

Missile::~Missile()
{

}

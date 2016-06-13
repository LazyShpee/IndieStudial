#include "IncludeIrrlicht.hpp"
#include "Player.hpp"
#include <iostream>
#include <cmath>
#include <math.h>
#include "Instance.hpp"

#define MOVE_SCALE 10

Player::Player(irr::u32 uuid, iscene::ISceneManager *smgr)
{
	this->smgr = smgr;
	this->entity = new Entity(0, uuid, smgr);
	this->_vehicle.setConfig(Vehicle::getDefaultConfig());
	this->_vehicle.setInput(this->_input);

	// Ce que charpe à rajouter
	this->has_missile = false;
	this->stopped_fire = false;

	this->setCollisions(smgr);
	this->_lastPlayerSize = core::Instance::PlayerList.size();
}

Player::~Player()
{
}

Entity * Player::getEntity() const {
	return this->entity;
}

void Player::update(irr::f32 dt, iscene::ISceneManager *smgr)
{
  unsigned int tmp;
  if (this->_lastPlayerSize != (tmp = core::Instance::PlayerList.size()))
    {
      this->redoCollisions(smgr);
      this->_lastPlayerSize = tmp;
    }

  iscene::IAnimatedMeshSceneNode *node = this->entity->getNode();
  icore::vector3df pos = node->getPosition();
  icore::vector3df rot = node->getRotation();

  Vector::Vec2 p(pos.X / MOVE_SCALE, pos.Z / MOVE_SCALE);
  Vector::Vec2 kek = this->_vehicle.getPosition();
  if (abs(p.x - kek.x) > 0.1 || abs(p.y - kek.y) > 0.001)
    {
      std::cout << "Calmez vous !" << std::endl;
      this->_vehicle.calmezVous(M_PI, 10.f);
    }

  this->_vehicle.setPosition(p);

  this->_vehicle.update((double)dt);

  Vector::Vec2 vehiclePos = this->_vehicle.getPosition();
  pos.X = vehiclePos.x * MOVE_SCALE;
  pos.Z = vehiclePos.y * MOVE_SCALE;
  rot.Y = (-this->_vehicle.getHeading() / M_PI * 180.f);
  node->setPosition(pos);
  node->setRotation(rot);

  //Debug : pour tester ce qui collisionne :)
  unsigned int i = 0;
  while (i < this->entity->getWorldCollision().size())
    {
      if (this->entity->getWorldCollision()[i]->collisionOccurred())
	{
	  // irr::core::vector3df lole = 
	  this->entity->getWorldCollision()[i]->getCollisionPoint();
	  // irr::core::vector3df keko = 
	  this->entity->getNode()->getPosition();
	  //std::cout << lole.X << " - " << lole.Y << " - " << lole.Z << std::endl;
	}
      i++;
    }

  // Ce que charpe à rajouter
  if ((this->_input & core::GAME_FIRE) && this->stopped_fire)
    fire_blipblipblipblipblip();
}

void					Player::redoCollisions(iscene::ISceneManager *smgr)
{
	this->entity->getNode()->removeAnimators();
	this->entity->getWorldCollision().clear();
	this->setCollisions(smgr);
}

void					Player::setCollisions(iscene::ISceneManager *smgr)
{
	//Ce que jeune poney a changé
	icore::array<irr::scene::ISceneNode*>	nodes;

	smgr->getSceneNodesFromType(irr::scene::ESNT_ANY, nodes); // Find all nodes

	for (irr::u32 i = 0; i < nodes.size(); ++i)
	{
		iscene::ISceneNode*								node = nodes[i];
		iscene::ITriangleSelector*						selector = 0;
		iscene::ISceneNodeAnimatorCollisionResponse*	anim = 0;

		if (node != this->entity->getNode())
		{
			switch (node->getType())
			{
			case irr::scene::ESNT_OCTREE:
				selector = smgr->createOctreeTriangleSelector(((irr::scene::IMeshSceneNode*)node)->getMesh(), node);
				this->entity->getNode()->setTriangleSelector(selector);

				anim = smgr->createCollisionResponseAnimator(selector,
					this->entity->getNode(), this->entity->getNode()->getTransformedBoundingBox().getExtent(),
					irr::core::vector3df(0, -5.f, 0));

				selector->drop();
				this->entity->getNode()->addAnimator(anim);
				this->entity->addWorldCollision(anim);
				anim->drop();
				break;

			case irr::scene::ESNT_ANIMATED_MESH:
				selector = smgr->createTriangleSelectorFromBoundingBox(node);
				this->entity->getNode()->setTriangleSelector(selector);

				anim = smgr->createCollisionResponseAnimator(selector,
					this->entity->getNode(), this->entity->getNode()->getTransformedBoundingBox().getExtent(),
					irr::core::vector3df(0, 0, 0));

				selector->drop();
				this->entity->getNode()->addAnimator(anim);
				this->entity->addWorldCollision(anim);//getWorldCollision().push_back(anim);
				anim->drop();
				break;

			default:
				break;
			}
		}
	}
}

// Ce que charpe à rajouter
void Player::fire_blipblipblipblipblip()
{
	this->_missiles.push_back(new Missile(this->entity->getNode(), this->smgr));
	this->stopped_fire = false;
	//MenuLoop::entities.push_back(this->_bonus);
}

void Player::setInput(irr::u32 const input)
{
  this->_input = input;
}

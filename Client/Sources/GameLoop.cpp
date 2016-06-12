#include "Loop.hpp"
#include "Constants.hpp"
#include "Camera.hpp"
#include "Entity.hpp"
#include "Rayzal.hpp"

core::GameLoop::GameLoop(device_t *device, rayzal::Peer *peer)
  : Loop(device, L"Suck My Wheels"), _peer(peer)
{
}

core::GameLoop::~GameLoop(void)
{
}

bool	core::GameLoop::_init(void)
{
  this->_device->smgr->
    addCameraSceneNode(0, icore::vector3df(0,0,0),
		       icore::vector3df(0,0,0));	// Nodes and meshes to print 
  iscene::IAnimatedMesh *map =
    this->_device->smgr->getMesh(ASSETS_DIR"/map/awp_india.obj");

  if (map)
    {
      this->_map_node = this->_device->smgr->addOctreeSceneNode(map->getMesh(0), 0, -1, 1024);
      if (this->_map_node)
	{
	  this->_map_node->setMaterialFlag(ivideo::EMF_LIGHTING, false);
	  this->_map_node->setPosition(icore::vector3df(0, 0, 0));
	  this->_map_node->setName("map");
	}
    }

  (void)core::gameInfo;
  // ##########################################################################################
  // >>>>>>>>>>>>>> create a new entity from uuid from core::gameInfos <<<<<<<<<<<<<<<<<<<<<<<<
  //this->_player = new Player(std::string(ASSETS_DIR"/car/Avent.obj"),
  //			     this->_device->smgr);
  // ##########################################################################################

  // iscene::ISceneNode *playerNode = this->_player->getNode();
  // playerNode->setScale(icore::vector3df(2.0f, 2.0f, 2.0f));
  // playerNode->setPosition(icore::vector3df(100, 100, 100));
  // playerNode->setMaterialFlag(ivideo::EMF_LIGHTING, false);
  // playerNode->setName("player");

  // if (ennemy_mesh)
  //   {
  //     ennemy_node = this->_device->smgr->addAnimatedMeshSceneNode(ennemy_mesh);
  //     ennemy_node->setPosition(icore::vector3df(120, 84, 100));
  //     ennemy_node->setMaterialFlag(ivideo::EMF_LIGHTING, false);
  //     ennemy_node->setName("enemy");
  //   }

  this->_player = new Entity(0, core::selfInfo.uuid, this->_device->smgr);

  this->_camera = new Camera(this->_device->ptr);

  return (OK_CODE);
}
#include <iostream>
int	core::GameLoop::_loop(void)
{
  rayzal::InputPacket inputPacket;
  inputPacket.uuid = core::selfInfo.uuid;
  inputPacket.PacketType = rayzal::ID_INPUT;
  inputPacket.input = core::Receiver::inputs;
  this->_peer->sendPacket(&inputPacket);

  if (core::Receiver::inputs & core::GUI_MENU)
    return (ERROR_CODE);

  if (core::Receiver::scroll != 0)
    {
      this->_camera->addDistance(5 * core::Receiver::scroll);
      core::Receiver::scroll = 0;
    }

  this->_camera->updateCamera(this->_player);
  this->_device->driver->beginScene(true, true, ivideo::SColor(255,200,200,200));

  this->_map_node->render();
  std::vector<Entity *>::const_iterator it = core::EntityList.cbegin();
  while (it != core::EntityList.cend()) {
    std::cout << "blblblbl la loooooooooooooop" << std::endl;
	  (*it)->getNode()->render();
	  it++;
  }

  this->_device->driver->endScene();
  return (OK_CODE);
}

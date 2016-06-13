#include <iostream>
#include <fstream>
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
  (void)core::gameInfo;
  // ##########################################################################################
  // >>>>>>>>>>>>>> create a new entity from uuid from core::gameInfos <<<<<<<<<<<<<<<<<<<<<<<<
  //this->_player = new Player(std::string(ASSETS_DIR"/car/Avent.obj"),
  //			     this->_device->smgr);
  // ##########################################################################################

  this->_device->driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);
  this->_device->driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_16_BIT, false);
  this->_device->driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

  this->_device->smgr->addCameraSceneNode(0,
	  icore::vector3df(0, 0, 0),
	  icore::vector3df(0, 0, 0));	// Nodes and meshes to print 
  iscene::IAnimatedMesh			*map = this->_device->smgr->getMesh(MAP_MESH_PATH);
  iscene::IMeshSceneNode			*map_node = 0;
  iscene::ISceneNode* skybox = this->_device->smgr->addSkyBoxSceneNode(
	  this->_device->driver->getTexture(ASSETS_DIR"/sky/test_shadowmoon_moon01.png"),
	  this->_device->driver->getTexture(ASSETS_DIR"/sky/test_shadowmoon_moon01.png"),
	  this->_device->driver->getTexture(ASSETS_DIR"/sky/test_shadowmoon_moon01.png"),
	  this->_device->driver->getTexture(ASSETS_DIR"/sky/test_shadowmoon_moon01.png"),
	  this->_device->driver->getTexture(ASSETS_DIR"/sky/test_shadowmoon_moon01.png"),
	  this->_device->driver->getTexture(ASSETS_DIR"/sky/test_shadowmoon_moon01.png"));
  skybox->setRotation(irr::core::vector3df(0.f, 0.f, 0.f));

  if (map)
  {
	  map_node = this->_device->smgr->addOctreeSceneNode(map->getMesh(0), 0, -1, 1024);
	  if (map_node)
	  {
		  map_node->setMaterialFlag(ivideo::EMF_LIGHTING, false);
		  map_node->setPosition(icore::vector3df(150, 0, 100));
		  map_node->setScale(icore::vector3df(10.0f, 10.0f, 10.0f));
		  map_node->setName("map");
	  }
  }

  this->_player = new Entity(/*core::selfInfo.car_model*/40, core::selfInfo.uuid, this->_device->smgr);

  this->_camera = new Camera(this->_device->ptr);

  std::ofstream outfile ("done");
  outfile << "#JeSuisLegit" << std::endl;
  outfile.close();
  return (OK_CODE);
}

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

  // std::vector<Entity *>::const_iterator it = core::EntityList.cbegin();
  // while (it != core::EntityList.cend()) {
  //   std::cout << "blblblbl la loooooooooooooop" << std::endl;
  // 	  (*it)->getNode()->render();
  // 	  it++;
  // }

  this->_device->smgr->drawAll();
  this->_device->driver->endScene();
  return (OK_CODE);
}

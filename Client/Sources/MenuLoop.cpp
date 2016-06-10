#include "Loop.hpp"
#include "Constants.hpp"
#include "Camera.hpp"

core::MenuLoop::MenuLoop(device_t *device)
  : Loop(device, L"Suck My Wheels")
{
}

bool	core::MenuLoop::_init(void)
{
  this->_device->smgr->addCameraSceneNode(0,
				    icore::vector3df(0,0,0),
				    icore::vector3df(0,0,0));
  return (OK_CODE);
}

int	core::MenuLoop::_loop(void)
{
  return (OK_CODE);
}

#include <stdio.h>

#include "Instance.hpp"
#include "Rayzal.hpp"
#include "Constants.hpp"

int main()
{
  core::device_t device;

  /* lib and device init */
  device.ptr = irr::createDevice(ivideo::EDT_NULL,
				 icore::dimension2d<irr::u32>(1280, 720), 16,
				 false, true, false);
  if (!device.ptr)
    return (ERROR_CODE);
  device.driver = device.ptr->getVideoDriver();
  device.smgr = device.ptr->getSceneManager();
  device.guienv = device.ptr->getGUIEnvironment();

  rayzal::Peer peer(4242);
  rayzal::ListenerThread listener(&peer, device.smgr);
  core::Instance instance(&device, &peer);
  if (instance.init())
    return (ERROR_CODE);
  while (device.ptr->run())
    instance.loop();
  device.ptr->drop();
  return (OK_CODE);
}

#include "Loop.hpp"
#include "Constants.hpp"

#if defined (_IRR_WINDOWS_) && ! defined (MSYS)
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

/* 
 * bonjour je suis le main
 * pour l'instant je contient l'init de la lib et la boucle de jeu
 */
int main()
{
  core::device_t device;
  core::Receiver receiver;
  core::ILoop *loop[2];
  int ret;

  /* lib and device init */
  device.ptr = irr::createDevice(ivideo::EDT_OPENGL,
	  icore::dimension2d<irr::u32>(1280, 720), 16,
				 false, true, false, &receiver);
  if (!device.ptr)
    return (ERROR_CODE);
  device.driver = device.ptr->getVideoDriver();
  device.smgr = device.ptr->getSceneManager();
  device.guienv = device.ptr->getGUIEnvironment();

  loop[0] = new core::GameLoop(&device);
  // loop[1] = new core::MenuLoop(&device);
  if (loop[0]->init())
    return (ERROR_CODE);
  // if (loop[1]->init())
  //   return (ERROR_CODE);

  ret = 0;
  while (device.ptr->run())
    ret = loop[ret]->loop();
  device.ptr->drop();
  // delete loop[1];
  delete loop[0];
  return (OK_CODE);
}

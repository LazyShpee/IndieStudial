#include "Loop.hpp"
#include "Constants.hpp"

#ifdef _WIN32
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
  int status;

  /* lib and device init */
  device.ptr = irr::createDevice(ivideo::EDT_OPENGL,
				 icore::dimension2d<irr::u32>(1280, 720), 16,
				 false, true, false, &receiver);
  if (!device.ptr)
    return (ERROR_CODE);
  device.driver = device.ptr->getVideoDriver();
  device.smgr = device.ptr->getSceneManager();
  device.guienv = device.ptr->getGUIEnvironment();

  rayzal::Peer peer("localhost");
  rayzal::ListenerThread listener(device.smgr, &peer);
  while ((status = listener.wait_connection()) != OK_CONNECTION)
    {
      if (status == ERROR_CODE)
	return (ERROR_CODE); // next update of this loop will be to try again the connection attempt
      usleep(500);
    }
  // MenuLoop will be defined here when it will be working ^^'
  // and then another method of ListenerThread will be added to init the peer attempt
  loop[0] = new core::GameLoop(&device, &peer);
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

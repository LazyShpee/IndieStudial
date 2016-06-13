#include "Loop.hpp"
#include "Constants.hpp"

#ifdef _WIN32
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
#include <iostream>

std::vector<Entity *> &core::getEntitylist(void)
{
  static std::vector<Entity *> EntityList;
  return (EntityList);
}

/*
 * bonjour je suis le main
 * pour l'instant je contient l'init de la lib et la boucle de jeu
 */
int main(int ac, char **av)
{
  core::device_t device;
  core::Receiver receiver;
  core::GameLoop *loop;
  int ret;
  int status;
  char const *address;
  unsigned int port;

  if (ac != 4)
    {
      address = "localhost";
      port = 4242U;
      memcpy(core::getSelfInfo()->nick, "ta maman", 9);
    }
  else
    {
      address = *(av + 1);
      port = atoi(*(av + 2));
      memcpy(core::getSelfInfo()->nick, *(av + 3), strlen(*(av + 3)));
    }

  /* lib and device init */
  device.ptr = irr::createDevice(ivideo::EDT_OPENGL,
				 icore::dimension2d<irr::u32>(1280, 720), 16,
				 false, true, false, &receiver);
  if (!device.ptr)
    return (ERROR_CODE);
  device.driver = device.ptr->getVideoDriver();
  device.smgr = device.ptr->getSceneManager();
  device.guienv = device.ptr->getGUIEnvironment();

  rayzal::Peer peer(address, port);
  rayzal::ListenerThread listener(device.smgr, &peer);
  while ((status = listener.wait_connection()) != OK_CONNECTION)
    {
      std::cout << "bon j'attend..." << std::endl;
      if (status == ERROR_CODE)
        goto exit; // next update of this loop will be to try again the connection attempt
      SLEEP(500);
    }
  std::cout << "bon la euh sa va c bon euh voila hein " << core::getSelfInfo()->uuid << std::endl;
  loop = new core::GameLoop(&device, &peer);
  if (loop->init())
    goto exit;
  
  ret = 0;
  while (!ret && device.ptr->run())
    ret = loop->loop();
  delete loop;
 exit:
  listener.join();
  device.ptr->drop();
  return (OK_CODE);
}

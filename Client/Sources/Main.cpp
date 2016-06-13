#include "Loop.hpp"
#include "Constants.hpp"
#include <string.h>
#include <iostream>
#include <fstream>

#ifdef _WIN32
# pragma comment(lib, "Irrlicht.lib")
//# pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
#include <iostream>
/*
 * bonjour je suis le main
 * pour l'instant je contient l'init de la lib et la boucle de jeu
 */
int main(int ac, char **av)
{
  core::device_t device;
  core::Receiver receiver;
  core::ILoop *loop[2];
  int ret;
  int status;
  char const *address;
  unsigned int port;
  (void)core::gameInfo;

  if (ac != 4)
    {
      address = "localhost";
      port = 4242U;
      strcpy(core::selfInfo.nick, "ta maman");
    }
  else
    {
      address = *(av + 1);
      port = atoi(*(av + 2));
      strcpy(core::selfInfo.nick, *(av + 3));
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

  // MenuLoop will be defined here when it will be working ^^'
  // and then another method of ListenerThread will be added to init the peer attempt
  loop[0] = new core::GameLoop(&device, &peer);
  // loop[1] = new core::MenuLoop(&device);
  if (loop[0]->init())
    goto exit;
  // if (loop[1]->init())
  //   return (ERROR_CODE);

  std::ofstream outfile ("done");
  outfile << "#JeSuisLegit" << std::endl;
  outfile.close();

  ret = 0;
  while (!ret && device.ptr->run())
    ret = loop[ret]->loop();
  // delete loop[1];
  delete loop[0];
 exit:

  std::ofstream outfile ("done");
  outfile << "#JeSuisLegit" << std::endl;
  outfile.close();

  listener.join();
  device.ptr->drop();
  return (OK_CODE);
}

#ifndef CONSTANT_HPP_
# define CONSTANT_HPP_

# ifdef LINUX
#  include <unistd.h>
# endif
# ifdef WINDOWS
#  include <windows.h>
# endif

# include "MessageIdentifiers.h"
#include "TCPInterface.h"
#include "ConsoleServer.h"
#include "RakNetCommandParser.h"
#include "TelnetTransport.h"

#include "RakPeerInterface.h"
#include "LogCommandParser.h"
#include "GetTime.h"
#include "RakNetTransport2.h"
#include "LinuxStrings.h"
#include <stdio.h>
#include <string>

# define MAX_PLAYERS 4
# define DEFAULT_SERVER_PORT 4242

# define SLEEP(sleepMs) Sleep(sleepMs);
# ifdef LINUX
#  define SLEEP(sleepMs) usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
# endif
# ifdef WINDOWS
#  define SLEEP(sleepMs) Sleep(sleepMs);
# endif

enum PacketType {
	ID_DEBUG = ID_USER_PACKET_ENUM + 1,
	ID_ENTITY,
	ID_MESSAGE,
};

#endif
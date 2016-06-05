#ifndef CONSTANT_HPP_
# define CONSTANT_HPP_

# ifdef LINUX
#  include <unistd.h>
# endif
# ifdef WINDOWS
#  include <windows.h>
# endif

# include "MessageIdentifiers.h"

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
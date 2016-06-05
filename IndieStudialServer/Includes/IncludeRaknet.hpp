#ifndef INCLUDE_RACKNET_HPP_
# define INCLUDE_RACKNET_HPP_

# ifdef _IRR_WINDOWS_
#  include "TCPInterface.h"
#  include "ConsoleServer.h"
#  include "RakNetCommandParser.h"
#  include "TelnetTransport.h"
#  include "RakPeerInterface.h"
#  include "LogCommandParser.h"
#  include "GetTime.h"
#  include "RakNetTransport2.h"
#  include "LinuxStrings.h"
# else
#  include "raknet/TCPInterface.h"
#  include "raknet/ConsoleServer.h"
#  include "raknet/RakNetCommandParser.h"
#  include "raknet/TelnetTransport.h"
#  include "raknet/RakPeerInterface.h"
#  include "raknet/LogCommandParser.h"
#  include "raknet/GetTime.h"
#  include "raknet/RakNetTransport2.h"
#  include "raknet/LinuxStrings.h"
# endif

#endif // INCLUDE_RACKNET_HPP_

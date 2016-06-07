#ifndef INCLUDE_RACKNET_HPP_
# define INCLUDE_RACKNET_HPP_

# ifdef _IRR_WINDOWS_
#  include "RakPeerInterface.h"
#  include "RakNetTypes.h"
#  include "MessageIdentifiers.h"
# else
#  include "raknet/RakPeerInterface.h"
#  include "raknet/RakNetTypes.h"
#  include "raknet/MessageIdentifiers.h"
# endif

#endif // INCLUDE_RACKNET_HPP_
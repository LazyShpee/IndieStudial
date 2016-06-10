#ifndef INSTANCE_HPP_
# define INSTANCE_HPP_

# include <vector>

# include "IncludeIrrlicht.hpp"
# include "Player.hpp"

namespace core
{
  class Instance
  {
    core::device_t *_device;
    rayzal::Peer *_peer;
    irr::u32 _before;
  public:
    static std::vector<Player *> PlayerList;
  public:
    Instance(core::device_t *device, rayzal::Peer *peer);
  public:
    bool init(void);
    int loop(void);
  };

  irr::u32 UUID();
}

#endif /* INSTANCE_HPP_ */

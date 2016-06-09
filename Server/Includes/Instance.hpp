#ifndef INSTANCE_HPP_
# define INSTANCE_HPP_

# include "IncludeIrrlicht.hpp"

namespace core
{
  class Instance
  {
    core::device_t *_device;
    irr::u32 _before;
  public:
    static irr::u32 input;
  public:
    Instance(core::device_t *device);
  public:
    bool init(void);
    int loop(void);
  }
};

#endif /* INSTANCE_HPP_ */

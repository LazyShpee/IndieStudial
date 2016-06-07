#ifndef INCLUDE_IRRLICHT_HPP_
# define INCLUDE_IRRLICHT_HPP_

# ifdef _IRR_WINDOWS_
#  include <irrlicht.h>
# else
#  include <irrlicht/irrlicht.h>
# endif
namespace iscene = irr::scene;
namespace icore = irr::core;
namespace ivideo = irr::video;
namespace igui = irr::gui;

namespace core
{
  enum input_type
    {
      MOVE_FOWARD = 1,
      MOVE_BACK = 1 << 1,
      MOVE_LEFT = 1 << 2,
      MOVE_RIGHT = 1 << 3,
      MOVE_REVERSE = 1 << 4,
      MOVE_STAP = 1 << 5,
      GAME_FIRE = 1 << 6,
      GUI_MENU = 1 << 7,
      GUI_SCREEN = 1 << 8
    };
  enum { KEYS_COUNT = 9 };

  class Receiver: public irr::IEventReceiver
  {
  private: // private attributes
    irr::EKEY_CODE _irr_keys[KEYS_COUNT];
    input_type const _core_keys[KEYS_COUNT];
    input_type match_irr_keys[irr::KEY_KEY_CODES_COUNT];
  public: // public attributes
    static irr::u32 inputs;
    static irr::u32 buttons;
    static irr::f32 scroll;
  public: // constructors and operators
    Receiver(void);
  private: // private methods
    bool match_input(irr::EKEY_CODE const code) const;
  public: // public methods
    bool OnEvent(irr::SEvent const &event);
  };

  struct device_t
  {
    irr::IrrlichtDevice *ptr;
    ivideo::IVideoDriver *driver;
    iscene::ISceneManager *smgr;
    igui::IGUIEnvironment *guienv;
  };
}

#endif // INCLUDE_IRRLICHT_HPP_

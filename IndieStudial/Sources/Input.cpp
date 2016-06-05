#include "IncludeIrrlicht.hpp"
#include <iostream>

int core::Receiver::inputs = 0;
int core::Receiver::buttons = 0;
irr::f32 core::Receiver::scroll = 0;

// _irr_keys tab will not always be hard coded
core::Receiver::Receiver()
  : _irr_keys
{ irr::KEY_KEY_Z, irr::KEY_KEY_Q, irr::KEY_KEY_S, irr::KEY_KEY_D,
    irr::KEY_LCONTROL, irr::KEY_SPACE, irr::KEY_KEY_F, irr::KEY_ESCAPE, irr::KEY_F12 },
    _core_keys
    { MOVE_FOWARD, MOVE_LEFT, MOVE_BACK, MOVE_RIGHT, MOVE_REVERSE,
	MOVE_STAP, GAME_FIRE, GUI_MENU, GUI_SCREEN }
{
  int ct;

  ct = -1;
  while (++ct < KEYS_COUNT)
    this->match_irr_keys[this->_irr_keys[ct]] = this->_core_keys[ct];
}

bool core::Receiver::match_input(irr::EKEY_CODE const code) const
{
  int ct = -1;
  while (++ct < KEYS_COUNT)
    if (code == this->_irr_keys[ct])
      return (true);
  return (false);
}

bool		core::Receiver::OnEvent(irr::SEvent const &event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT
      && match_input(event.KeyInput.Key))
    {
      if (event.KeyInput.PressedDown)
	core::Receiver::inputs |= this->match_irr_keys[event.KeyInput.Key];
      else
	core::Receiver::inputs &= ~(this->match_irr_keys[event.KeyInput.Key]);
    }
  if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    if (event.MouseInput.Wheel)
      core::Receiver::scroll = event.MouseInput.Wheel;
  return false;
}

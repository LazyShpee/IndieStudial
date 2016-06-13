#ifndef PLAYER_H
# define PLAYER_H

# define _USE_MATH_DEFINES
# include <vector>
# include <cmath>

# include "Vehicle.hpp"
# include "Entity.hpp"
# include "Missile.hpp"

class Player
{
private:
  Entity *entity;
  Vehicle::Car _vehicle;
  iscene::ISceneManager *smgr;
  std::vector<Missile *> _missiles;
  irr::u32 _input;
  irr::u32 _lastPlayerSize;
public:
  bool stopped_fire;
  bool has_missile;

public:
  Player(irr::u32 uuid, irr::u32 model, iscene::ISceneManager *);
  ~Player();

  void update(irr::f32 dt, iscene::ISceneManager *smgr);

  void setConfig(Vehicle::Config *cfg);

  void setCollisions(iscene::ISceneManager *smgr);
  void redoCollisions(iscene::ISceneManager *smgr);

  Entity *getEntity() const;
  void setInput(irr::u32 const input);

  void fire_blipblipblipblipblip();
};

#endif

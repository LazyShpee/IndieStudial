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
  Entity entity;
  Vehicle::Car _vehicle;
  iscene::ISceneManager *smgr;
  std::vector<Missile *> _missiles;
  irr::u32 _input;
public:
  bool stopped_fire;
  bool has_missile;

public:
  Player(std::string const &, iscene::ISceneManager *);
  ~Player();

  void update(irr::f32 dt);

  void setCollisions(iscene::ISceneManager* &smgr);

  Entity const &getEntity() const;
  void setInput(irr::u32 const input);

  void fire_blipblipblipblipblip();
};

#endif

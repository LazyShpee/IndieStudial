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
	Entity					entity;
	Vehicle::Car			_vehicle;
	iscene::ISceneManager	*smgr;

	// Ce que charpe à rajouter
	std::vector<Missile *>	_missiles;


public:
	Player(std::string const &, iscene::ISceneManager *);
	~Player();

	void					update(irr::f32 dt);

	void					setCollisions(iscene::ISceneManager* &smgr);

	Entity const &			getEntity() const;

	// Ce que charpe à rajouter
	void					fire_blipblipblipblipblip();
	bool	stopped_fire;
	bool	has_missile;
};

#endif

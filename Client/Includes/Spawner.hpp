#ifndef SPAWNER_HPP_
# define SPAWNER_HPP_

//# include "Bonus.hpp"
# include "Player.hpp"
# include "Entity.hpp"

class Spawner
{
private:
	Entity	entity;
	//Bonus *_bonus;
	//Bonus::Type _type;

	//void generateBonus(struct device_t *&);

public:
	Spawner(iscene::ISceneManager *);
	~Spawner();

	void giveBonusToPlayer(Player *&);
};

#endif /* !SPAWNER_HPP */

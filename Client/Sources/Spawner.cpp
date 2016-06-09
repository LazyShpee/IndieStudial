#include "Spawner.hpp"

Spawner::Spawner(iscene::ISceneManager *smgr) : entity(std::string(SPAWNER_MESH_PATH), std::string("missile"), smgr)
{
	//this->_type = (Bonus::Type)(rand() % NB_BONUS);
	//this->_type = Bonus::MISSILE;
	//this->generateBonus(device);
	
	this->entity.getNode()->setPosition(icore::vector3df(200.f, 0.f, 200.f));
}

Spawner::~Spawner()
{

}

/*void Spawner::generateBonus(struct device_t *&device)
{
	this->_bonus = new Bonus(device, this->_type);
}*/

void Spawner::giveBonusToPlayer(Player *&player)
{
	player->has_missile = true;
	/*player->setBonus(this->_bonus);
	this->_bonus = NULL;*/
}

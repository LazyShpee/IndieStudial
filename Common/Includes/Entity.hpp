#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <string>
# include <vector>

# include "IncludeIrrlicht.hpp"
# include "Rayzal.hpp"

struct EntityType {
	unsigned char type;
	const char *meshPath;
};

const EntityType EntityDescription[] =
  {
    { 0, "mesh_player_car.obj" },
    { 4, "mesh_player_truck.obj" },
    { 5, "mesh_missile.obj" },
    { 0, 0 }
  };

class Entity {
private:
  unsigned char type;
  unsigned int uuid;
  iscene::ISceneManager *smgr;
  iscene::IAnimatedMesh *mesh;
  iscene::IAnimatedMeshSceneNode *node;
  std::vector<iscene::ISceneNodeAnimatorCollisionResponse*> worldCollision;

public:
  Entity(std::string const & meshPath,
	 std::string const & name, iscene::ISceneManager *smgr);
  Entity(rayzal::EntityPacket const *packet, iscene::ISceneManager *smgr);
  Entity(unsigned char type, unsigned int uuid, iscene::ISceneManager *smgr);
  ~Entity();

  iscene::IAnimatedMesh *getMesh() const;
  iscene::IAnimatedMeshSceneNode *getNode() const;

  //void setWorldCollision(std::vector<iscene::ISceneNodeAnimatorCollisionResponse*> worldCollision);
  void addWorldCollision(iscene::ISceneNodeAnimatorCollisionResponse *anim);
  std::vector<iscene::ISceneNodeAnimatorCollisionResponse*> getWorldCollision() const;
  rayzal::EntityPacket const *getPacket(void) const;

  void applyPacket(rayzal::EntityPacket const *packet);
  void applyPacket(rayzal::BasicPacket const *packet);
  irr::u32 getUUID();
private:
  void updateEntity(rayzal::EntityPacket const *packet);
};

#endif

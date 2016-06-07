#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <string>
# include <vector>

# include "IncludeIrrlicht.hpp"
# include "Rayzal.hpp"

// INSEREZ ICI LES TABLEAUX CONSTANTS POUR AVOIR LE NAME ET LE MESH-PATH

class Entity {
private:
  iscene::ISceneManager *smgr;
  iscene::IAnimatedMesh *mesh;
  iscene::IAnimatedMeshSceneNode *node;
  std::vector<iscene::ISceneNodeAnimatorCollisionResponse*> worldCollision;

public:
  Entity(std::string const & meshPath,
	 std::string const & name, iscene::ISceneManager *smgr);
  Entity(EntityPacket const *packet, iscene::ISceneManager *smgr);

  iscene::IAnimatedMesh *getMesh() const;
  iscene::IAnimatedMeshSceneNode *getNode() const;

  //void setWorldCollision(std::vector<iscene::ISceneNodeAnimatorCollisionResponse*> worldCollision);
  void addWorldCollision(iscene::ISceneNodeAnimatorCollisionResponse *anim);
  std::vector<iscene::ISceneNodeAnimatorCollisionResponse*> getWorldCollision() const;
  EntityPacket const *getPacket(void) const;

  template <class T>
  void applyPacket(T const *packet)
  {
    // INSEREZ ICI LE CODE QUI VA SOIT CALL this->updateEntity soit ou delete this
  }

private:
  void updateEntity(EntityPacket const *packet);
};

#endif

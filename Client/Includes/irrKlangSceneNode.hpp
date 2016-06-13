#ifndef __IRRKLANG_SCENE_NODE_H_INCLUDED__
#define __IRRKLANG_SCENE_NODE_H_INCLUDED__

// This file contains a scene node for the Irrlicht engine which is able to
// play back sounds and music in 3D. Just place it into 3d space and set
// what sound it should play.
// It uses the free irrKlang sound engine (http://www.ambiera.com/irrklang).
// This file also contains a sound engine factory, CIrrKlangSceneNodeFactory. Just 
// register this factory in your scene manager, and you will be able to load and
// save irrKlang scene nodes from and into .irr files:
//
// audirr::io::ISoundEngine* soundEngine = createIrrKlangDevice();
// CIrrKlangSceneNodeFactory* factory = new CIrrKlangSceneNodeFactory(soundEngine, sceneManager);
// sceneManager->registerSceneNodeFactory(factory);
// factory->drop();

#ifdef _WIN32
# include <irrlicht.h>
#else
# include <irrlicht/irrlicht.h>
#endif
#include <irrKlang.h>
using namespace irrklang;
//! A scene node for  playing 3d audio using the free irrKlang sound engine.
/** Use it like this:
\begincode
irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
IrrlichtDevice* device = createDevice(video::EDT_OPENGL, irr::core::dimension2d<irr::s32>(640, 480), 16, false);
irr::scene::ISceneManager* smgr = device->getSceneManager();
// .. other code here
CIrrKlangSceneNode* soundNode =
new CIrrKlangSceneNode(soundEngine, smgr->getRootSceneNode(), smgr, 666);
soundNode->setSoundFilename("yourfile.wav");
soundNode->setMinMaxSoundDistance(30.0f); // influences the distance where the sound can be heard
soundNode->setRandomMode(1000, 5000); // plays sound multiple times with random interval
// other modes would be:
// soundNode->setLoopingStreamMode()
// or
// soundNode->setPlayOnceMode();
soundNode->drop();
\endcode
*/
class CIrrKlangSceneNode : public irr::scene::ISceneNode
{
public:

	CIrrKlangSceneNode(irrklang::ISoundEngine* soundEngine,
		irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id);
	~CIrrKlangSceneNode();

	// play modes:

	//! Sets the play mode to 'play once', a sound file is played once, and 
	//! the scene node deletes itself then, if wished.
	void setPlayOnceMode(bool deleteWhenFinished = false);

	//! Sets the play mode to 'looping stream', plays a looped sound over and over again.
	void setLoopingStreamMode();

	//! Sets the play mode to 'random'. Plays a sound with a variable, random interval
	//! over and over again.
	//! \param minTimeMsInterval: Minimal wait time in milli seconds before the sound is played again.
	//! \param maxTimeMsInterval: Maximal wait time in milli seconds before the sound is played again.
	void setRandomMode(int minTimeMsInterval = 1000, int maxTimeMsInterval = 5000);

	// Sound parameters

	//! Sets the sound filename to play
	void setSoundFileName(const char* soundFilename);

	//! Gets the sound filename to play
	const char* getSoundFileName() const;

	//! Sets the minimal and maximal 3D sound distances.
	//! Set to negative values if you want to use the default values of the sound engine.
	void setMinMaxSoundDistance(irr::f32 minDistance = 1.0f, irr::f32 maxDistance = 10000000.0f);

	//! stops playback, releases sound, sets playmode to 'nothing'
	void stop();

	// rendering functions:

	virtual void OnAnimate(irr::u32 timeMs);
	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual irr::scene::ESCENE_NODE_TYPE getType() const;
	ISceneNode* clone(ISceneNode* newParent, irr::scene::ISceneManager* newManager);
	void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options);
	void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options);

protected:

	enum EPlayMode
	{
		EPM_NOTHING = 0,
		EPM_RANDOM,
		EPM_LOOPING,
		EPM_ONCE
	};

	irr::core::aabbox3d<irr::f32> Box;
	irrklang::ISoundEngine* SoundEngine;
	irrklang::ISound* Sound;

	irr::core::stringc SoundFileName;
	irr::f32 MinDistance;
	irr::f32 MaxDistance;

	EPlayMode PlayMode;
	irr::u32 TimeMsDelayFinished;
	bool DeleteWhenFinished;
	irr::s32 MaxTimeMsInterval;
	irr::s32 MinTimeMsInterval;
	irr::s32 PlayedCount;
};



// own factory implementation to make it possible to load and save irrKlang scene
// nodes fomr and to .irr files. Create an instance of this and use
// ISceneManager::registerSceneNodeFactory() for this.
class CIrrKlangSceneNodeFactory : public irr::scene::ISceneNodeFactory
{
public:

	CIrrKlangSceneNodeFactory(irrklang::ISoundEngine* soundEngine, irr::scene::ISceneManager* mgr);
	~CIrrKlangSceneNodeFactory();

	virtual irr::scene::ISceneNode* addSceneNode(irr::scene::ESCENE_NODE_TYPE type, irr::scene::ISceneNode* parent = 0);
	virtual irr::scene::ISceneNode* addSceneNode(const irr::c8* typeName, irr::scene::ISceneNode* parent = 0);
	virtual irr::s32 getCreatableSceneNodeTypeCount();
	virtual const irr::c8* getCreateableSceneNodeTypeName(irr::s32 idx);
	virtual irr::scene::ESCENE_NODE_TYPE getCreateableSceneNodeType(irr::s32 idx);
	virtual const irr::c8* getCreateableSceneNodeTypeName(irr::scene::ESCENE_NODE_TYPE type);

private:

	irr::scene::ESCENE_NODE_TYPE getTypeFromName(const irr::c8* name);
	irr::scene::ISceneManager* Manager;
	irrklang::ISoundEngine* SoundEngine;
};

#endif

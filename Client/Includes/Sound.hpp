#ifndef SOUND_HPP_
# define SOUND_HPP_

# include "Constants.hpp"
# include "irrKlang.h"
# include "irrKlangSceneNode.hpp"

struct SoundType {
	unsigned char type;
	const char *soundPath;
};

const SoundType SoundDescription[] =
{
	{ 0, ASSETS_DIR"/snd/elevator.wav" },
	{ 1, ASSETS_DIR"/snd/sneakman.wav" },
	{ 0, 0 }
};

static CIrrKlangSceneNode *soundNode;

#endif /* !SOUND_HPP_ */
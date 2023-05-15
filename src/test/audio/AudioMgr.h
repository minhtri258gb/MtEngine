#ifndef __MT_AUDIO_MANAGER_H__
#define __MT_AUDIO_MANAGER_H__

#include "Sound.h"

namespace mt {
namespace audio {

class AudioMgr
{

public:

	// Forward
	AudioMgr();
	~AudioMgr();
	void clear();
	void update();

	// Native
	Sound* cacheSound(std::string filepath);
	void play(std::string filepath);

	// Stock

private:

	// Variable
	class AudioMgrImpl;
	AudioMgrImpl* impl;

};

}}

#endif

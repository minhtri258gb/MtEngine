#ifndef __MT_AUDIO_H__
#define __MT_AUDIO_H__

#include "AudioMgr.h"

#include "Sound.h"

namespace mt {
namespace audio {

class Audio
{
public:

	// Variable
	static Audio ins;
	AudioMgr mgr;

	// Forward
	void init();
	void close();
	void update();

	// Native
	std::vector<std::string> getListDevice();
	void setVolume(float); // 0.0f - 1.0f

	// Stock

};

}}

#endif

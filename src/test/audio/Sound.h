#ifndef __MT_SOUND_H__
#define __MT_SOUND_H__

/*
 * Create in AudioMgr - chacheSound
 * Delete channel at destructor of Sound Object
 */

namespace mt {
namespace audio {

class Sound
{
public:

	friend class AudioMgr;

	// Forward
	Sound();
	~Sound();

	// Native
	void play();
	void pause();
	void stop();
	bool isPlay();
	bool isPause();
	bool isStop();

	// Stock

private:

	// Variable
	class SoundImpl;
	SoundImpl* impl;

};

}}

#endif

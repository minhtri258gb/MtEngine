#ifndef __MT_AUDIO_H__
#define __MT_AUDIO_H__

namespace mt {
namespace audio {

class Audio
{
public:

	// Constructor
	Audio();
	~Audio();

	// General
	void init();
	void update();

	// Get / Set
	float getMasterVolume();
	void setMasterVolume(float);
	unsigned int getSampleVolume();
	void setSampleVolume(unsigned int);
	unsigned int getStreamVolume();
	void setStreamVolume(unsigned int);
	unsigned int getMusicVolume();
	void setMusicVolume(unsigned int);
};

}}

#endif

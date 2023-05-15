#define __MT_SOUND_CPP__

#include <iostream>

#include <bass/bass.h>

#include "common.h"
#include "Sound.h"

using namespace std;
using namespace mt::audio;

class Sound::SoundImpl
{
public:
	HCHANNEL channel;
};

Sound::Sound()
{
	// Impliment
	this->impl = new SoundImpl();
}

Sound::~Sound()
{
	// Delete object library
	BASS_ChannelFree(this->impl->channel);

	// Impliment
	delete this->impl;
}

void Sound::play()
{
	BASS_ChannelPlay(this->impl->channel, FALSE); // #TODO this return boolean
}

void Sound::pause()
{
	BASS_ChannelPause(this->impl->channel); // #TODO this return boolean
}

void Sound::stop()
{
	BASS_ChannelStop(this->impl->channel); // #TODO this return boolean
}

bool Sound::isPlay()
{
	return (BASS_ACTIVE_PLAYING == BASS_ChannelIsActive(this->impl->channel));
}

bool Sound::isPause()
{
	return (BASS_ACTIVE_PAUSED == BASS_ChannelIsActive(this->impl->channel));
}

bool Sound::isStop()
{
	return (BASS_ACTIVE_STOPPED == BASS_ChannelIsActive(this->impl->channel));
}

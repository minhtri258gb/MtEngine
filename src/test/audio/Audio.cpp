#define __MT_AUDIO_CPP__

#include <iostream>

#include <bass/bass.h>

#include "common.h"
#include "Audio.h"

using namespace std;
using namespace mt::audio;

Audio Audio::ins;

void Audio::init()
{
	BASS_Init(-1, 44100, 0, 0, NULL);
}

void Audio::close()
{
	this->mgr.clear();

	BASS_Stop();
	BASS_Free();
}

/*
 * - manager update
 */
void Audio::update()
{
	this->mgr.update();
}

vector<string> Audio::getListDevice()
{
	vector<string> result;
	BASS_DEVICEINFO info;
	for (int index = 1; BASS_GetDeviceInfo(index, &info); index++)
		if (info.flags & BASS_DEVICE_ENABLED)
			result.push_back(info.name);
	return result;
}

void Audio::setVolume(float value)
{
	BASS_SetVolume(value);
}

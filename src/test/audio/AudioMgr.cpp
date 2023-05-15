#define __MT_AUDIO_MANAGER_CPP__

#include <iostream>

#include <bass/bass.h>

#include "common.h"
#include "AudioMgr.h"

using namespace std;
using namespace mt::audio;

class AudioMgr::AudioMgrImpl
{
public:
	map<string, HSAMPLE> mapSamples;
	vector<Sound*> lstSoundTmp;
};

class Sound::SoundImpl
{
public:
	HCHANNEL channel;
};

AudioMgr::AudioMgr()
{
	// Implement
	this->impl = new AudioMgrImpl();
}

AudioMgr::~AudioMgr()
{
	// Implement
	delete this->impl;
}

void AudioMgr::clear()
{
	// Clear Model
	map<string, HSAMPLE>::iterator it;
	for (it = this->impl->mapSamples.begin(); it != this->impl->mapSamples.end(); it++)
		BASS_SampleFree(it->second);
	this->impl->mapSamples.clear();
}

void AudioMgr::update()
{
	// find sound stop and clear one
	// De tranh loi xoa phan tu trong list, chi xoa 1 phan tu
	// Viec xoa file tmp ko lien tuc va ko nhat thiet lam trong 1 frame
	for (vector<Sound*>::iterator it = this->impl->lstSoundTmp.begin(), itEnd = this->impl->lstSoundTmp.end(); it != itEnd; it++)
	{
		Sound* soundTmp = (*it);
		if (soundTmp->isStop())
		{
			delete soundTmp;
			this->impl->lstSoundTmp.erase(it);
			break;
		}
	}
}

Sound* AudioMgr::cacheSound(string filepath)
{
	// Get available or load sample
	HSAMPLE sample;
	if (this->impl->mapSamples.count(filepath) == 1)
		sample = this->impl->mapSamples.at(filepath);
	else
	{
		sample = BASS_SampleLoad(false, filepath.c_str(), 0, 0, 1, BASS_SAMPLE_MONO);
		this->impl->mapSamples.emplace(filepath, sample);
	}

	// create channel
	HCHANNEL channel = BASS_SampleGetChannel(sample, FALSE);

	// Create Object
	Sound* sound = new Sound();
	sound->impl->channel = channel;
	return sound;
}

void AudioMgr::play(string filepath)
{
	Sound* soundTmp = this->cacheSound(filepath);
	this->impl->lstSoundTmp.push_back(soundTmp);
	soundTmp->play();
}

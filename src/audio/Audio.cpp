#define __MT_AUDIO_CPP__

#define LOW_QUALITY 0

#if LOW_QUALITY
	#define MIXRATE 22050
#else
	#define MIXRATE 44100
#endif // LOW_QUALITY

//#define MAXCHANNEL 32 // 64

#include <bass/bass.h>

#include "common.h"
#include "graphic/Graphic.h"
#include "Audio.h"

using namespace mt;
using namespace mt::graphic;
using namespace mt::audio;


Audio::Audio() {
}

Audio::~Audio() {
	BASS_Stop();
	BASS_Free();
}

void Audio::init() {
	// Check version
	if (HIWORD(BASS_GetVersion()) != BASSVERSION)
		throw error("BASS_VERSION_INVAIL", "Incorrect version BASS loaded!");

	// Variable reference
//	listenerPos = engine.view->getPositionPointer();
//	listenerFront = engine.view->getVecLookPointer();

	// Device

	BASS_SetConfig(BASS_CONFIG_DEV_DEFAULT, 1);
	BASS_DEVICEINFO di;
	int a, device = -1;
	for (a = 1; BASS_GetDeviceInfo(a, &di); a++)
	{
//		std::cout << "Driver name: " << di.name << std::endl;
		device = a;
	}

	// Init
	if (!BASS_Init(device, MIXRATE, BASS_DEVICE_3D, 0, NULL))
		throw error("BASS_INIT_FAIL", "Can't initialize device!");

	// Set parameters
	// BASS_Set3DFactors(ACTUAL_UNIT, ACTUAL_UNIT, ACTUAL_UNIT);
//    FSOUND_SetSFXMasterVolume(255); // default 255
//    FSOUND_3D_SetDistanceFactor(ACTUAL_UNIT);
//    FSOUND_3D_SetRolloffFactor(1.0f); // default 1.0f

	BASS_Start();
}

void Audio::update() {
	vec3 position = Graphic::ins.camera.position;
	vec3 veclook = Graphic::ins.camera.forward;

	BASS_3DVECTOR pos, vel, front, top;
	pos.x = position.x;
	pos.y = position.y;
	pos.z = position.z;
	vel.x = 0.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;
	front.x = veclook.x;
	front.y = veclook.y;
	front.z = veclook.z;
	top.x = 0.0f;
	top.y = 1.0f;
	top.z = 0.0f;

	BASS_Set3DPosition(&pos, &vel, &front, &top);

	BASS_Apply3D();
}

float getMasterVolume() {
	return BASS_GetVolume();
}

void setMasterVolume(float volume) { // 0.0 - 1.0
	BASS_SetVolume(volume);
}

unsigned int getSampleVolume() {
	return BASS_GetConfig(BASS_CONFIG_GVOL_SAMPLE);
}

void setSampleVolume(unsigned int volume) { // 0 - 10000
	BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, volume);
}

unsigned int getStreamVolume() {
	return BASS_GetConfig(BASS_CONFIG_GVOL_STREAM);
}

void setStreamVolume(unsigned int volume) { // 0 - 10000
	BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, volume);
}

unsigned int getMusicVolume() {
	return BASS_GetConfig(BASS_CONFIG_GVOL_MUSIC);
}

void setMusicVolume(unsigned int volume) { // 0 - 10000
	BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, volume);
}

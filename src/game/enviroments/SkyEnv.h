#ifndef __MT_SKY_ENV_H__
#define __MT_SKY_ENV_H__

namespace mt {
namespace game {

class SkyEnv {

public:

	// Constructor
	SkyEnv(std::string name);
	~SkyEnv();

	// Forward
	void update();

	// Native

private:

	// Variables
	class SkyEnvImpl;
	SkyEnvImpl* impl;

};

}}

#endif

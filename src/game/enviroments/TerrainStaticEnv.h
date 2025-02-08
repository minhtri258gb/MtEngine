#ifndef __MT_TERRAIN_STATIC_ENV_H__
#define __MT_TERRAIN_STATIC_ENV_H__

namespace mt {
namespace game {

class TerrainStaticEnv {

public:

	// Constructor
	TerrainStaticEnv(std::string name);
	~TerrainStaticEnv();

	// Forward
	void update();

	// Native

private:

	// Variables
	class TerrainStaticEnvImpl;
	TerrainStaticEnvImpl* impl;

};

}}

#endif

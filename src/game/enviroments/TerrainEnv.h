#ifndef __MT_TERRAIN_ENV_H__
#define __MT_TERRAIN_ENV_H__

namespace mt {
namespace game {

class TerrainEnv {

public:

	// Constructor
	TerrainEnv(std::string name);
	~TerrainEnv();

	// Forward
	void update();

	// Native

private:

	// Variables
	class TerrainEnvImpl;
	TerrainEnvImpl* impl;
};

}}

#endif

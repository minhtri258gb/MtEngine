#ifndef __MT_DEBUG_FRAME_H__
#define __MT_DEBUG_FRAME_H__

#include "graphic/ShaderProgram.h"

namespace mt {
namespace graphic {

class DebugFrame
{

public:

	// Variables
	static ShaderProgram shader;

	// Constructor
	DebugFrame();
	~DebugFrame();

	// Load custom
	void loadVAO(std::vector<vec3> vertices, std::vector<unsigned int> indices);

	// General
	void render(vec3 pos, quat rot, vec3 scale);

private:

	// Variables
	class DebugFrameImpl;
	DebugFrameImpl* impl;

};

}}

#endif

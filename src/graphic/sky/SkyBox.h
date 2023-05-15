#ifndef __MT_SKYBOX_H__
#define __MT_SKYBOX_H__

#include "../ShaderProgram.h"
#include "Sun.h"

namespace mt {
namespace graphic {

class SkyBox
{
public:

	// Variables
	static ShaderProgram shader;
	Sun *sun;

	// Forwards
	SkyBox();
	~SkyBox();

	// Natives
	void init(std::string name);
	void render();

private:

	// Variable
	class SkyBoxImpl;
	SkyBoxImpl* impl;
};

}}

#endif

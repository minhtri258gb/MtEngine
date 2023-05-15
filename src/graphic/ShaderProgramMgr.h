#ifndef __MT_SHADER_PROGRAM_MANAGER_H__
#define __MT_SHADER_PROGRAM_MANAGER_H__

namespace mt {
namespace graphic {

class ShaderProgramMgr
{

public:

	// Variable

	// Forward
	ShaderProgramMgr();
	~ShaderProgramMgr();
	void init();
	void close();

	// Native
	void setSceneProj(mat4);
	void setSceneView(mat4);
	void setScreenProj(mat4);
	void setScreenView(mat4);
	void setCameraPosition(vec3);


private:

	// Forward

};

}}

#endif

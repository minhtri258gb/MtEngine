#ifndef __MT_GRAPHIC_H__
#define __MT_GRAPHIC_H__

#include "ShaderProgramMgr.h"
#include "models/ModelMgr.h"
#include "Scene.h"
// #include "Screen.h"
#include "Camera.h"
#include "hud/Text.h"

namespace mt {
namespace graphic {

class Graphic {

public:

	// Variable
	static Graphic ins;

	ShaderProgramMgr shaderProgramMgr;
	ModelMgr modelMgr;
	Scene scene;
	// Screen screen;
	Camera camera;
	Text text;

	// Forward
	Graphic();
	~Graphic();
	void init();
	void close();
	void update();
	void render();

	void addModel(Model* model, vec3* pos, quat* rot, vec3* scale);

	void processInput();
	void renderPre();
	void renderPost();

	// Native
	bool checkWindow();
	double getTime();

	void setDepthTest(bool value = true);
	void setDepthMark(bool);

	// Stock
	void cullFaceToogle(bool);
	void cullFaceBack(bool);
	void cullFaceClock(bool);
	void wireframe(bool);
	void blendToogle(bool);
	void blendFunc(int);

	int getPatchParameterMax();
	void setPatchParameter(int);

private:

	// Variable
	class GraphicImpl;
	GraphicImpl* impl;

};

}}

#endif

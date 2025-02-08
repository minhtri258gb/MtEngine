#ifndef __MT_GRAPHIC_H__
#define __MT_GRAPHIC_H__

#include "ShaderProgramMgr.h"
#include "models/ModelMgr.h"
#include "Scene.h"
#include "GUI.h"
#include "Camera.h"
#include "ui/Text.h"

namespace mt {
namespace graphic {

class Graphic {

public:

	// Variable
	static Graphic ins;

	ShaderProgramMgr shaderProgramMgr;
	ModelMgr modelMgr;
	Scene scene;
	GUI gui;
	Camera camera;
	Text text;

	// Forward
	Graphic();
	~Graphic();

	void init();
	void update();
	void render();
	void close();

	void addModel(Model* model, vec3* pos, quat* rot, vec3* scale);

	// void processInput();
	void renderPre();
	void renderPost();

	// Native
	bool checkWindow();
	double getTime();

	bool isShowCursor();
	void showCursor(bool toogle);

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

	friend class GUI;

};

}}

#endif

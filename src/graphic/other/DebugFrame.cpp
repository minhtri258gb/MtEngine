#define __MT_DEBUG_FRAME_CPP__

#include "common.h"
#include "graphic/Graphic.h"
#include "graphic/buffer/VertexArrayObject.h"
#include "DebugFrame.h"

using namespace std;
using namespace mt;
using namespace mt::graphic;


ShaderProgram DebugFrame::shader;


class DebugFrame::DebugFrameImpl
{
public:
	VertexArrayObject VAO;
};


DebugFrame::DebugFrame()
{
	// Implement
	impl = new DebugFrameImpl();
}

DebugFrame::~DebugFrame()
{
	// Implement
	delete impl;
}

void DebugFrame::loadVAO(vector<vec3> vertices, vector<unsigned int> indices)
{
	impl->VAO.init();
	impl->VAO.bind();
	impl->VAO.addAttribute(vertices);
	impl->VAO.addIndices(indices);
	impl->VAO.unbind();
}

void DebugFrame::render(vec3 _pos, quat _rot, vec3 _scale)
{
	// Frustumcull
	// if (!Graphic::ins.camera.frustumCulling.sphere(position, 0)); // #TODO
	// 	return;
	// if (!Graphic::ins.camera.frustumCulling.point(this->position))
	// 	return;

	// Shader
	this->shader.use();

	// Model mattrix
	mat4 matModel;
	matModel.translate(_pos);
	matModel.rotate(_rot);
	matModel.scale(_scale);
	this->shader.setMat4(2, matModel);

	// Prepare render
	Graphic::ins.cullFaceToogle(false);

	// VAO
	impl->VAO.bind();
	// VAO.renderTriangle();
	impl->VAO.drawElementTriangle();
	impl->VAO.unbind();

	// Post render
	Graphic::ins.cullFaceToogle(true);
}

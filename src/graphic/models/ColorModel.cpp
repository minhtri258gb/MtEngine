#define __MT_COLOR_MODEL_CPP__

#include "common.h"
#include "../Graphic.h"
#include "../buffer/VertexArrayObject.h"
#include "ColorModel.h"

using namespace std;
using namespace mt;
using namespace mt::graphic;


class ColorModel::ColorModelImpl
{
public:
	VertexArrayObject VAO;
};

ShaderProgram ColorModel::shader;


ColorModel::ColorModel()
{
	// Implement
	impl = new ColorModelImpl();
}

ColorModel::~ColorModel()
{
	// Implement
	delete impl;
}

void ColorModel::loadVAO(vector<vec3> vertices, vector<unsigned int> indices)
{
	impl->VAO.init();
	impl->VAO.bind();
	impl->VAO.addAttribute(vertices);
	impl->VAO.addIndices(indices);
	impl->VAO.unbind();
}

void ColorModel::render()
{
	// Frustumcull
	// if (!Graphic::ins.camera.frustumCulling.sphere(position, 0));
	// 	return;
	// if (!Graphic::ins.camera.frustumCulling.point(position));
	// 	return;

	// Shader
	this->shader.use();

	// Model mattrix
	mat4 matModel;
	matModel.translate(this->position);
	matModel.rotate(this->angle);
	matModel.scale(this->scale);
	shader.setMat4(2, matModel);

	// VAO
	impl->VAO.bind();
	// VAO.renderTriangle();
	impl->VAO.drawElementTriangle();
	impl->VAO.unbind();
}

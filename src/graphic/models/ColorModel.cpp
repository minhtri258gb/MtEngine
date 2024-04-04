#define __MT_COLOR_MODEL_CPP__

// #define LOG cout << __FILE__ << " | " << __LINE__ << '\n';

#include "common.h"
#include "../Graphic.h"
#include "../buffer/VertexArrayObject.h"
#include "../texture/Texture.h"
#include "ColorModel.h"

using namespace std;
using namespace mt;
using namespace mt::graphic;


ShaderProgram ColorModel::shader;


class ColorModel::ColorModelImpl
{
public:
	VertexArrayObject VAO;
};


ColorModel::ColorModel()
{
	// Implement
	impl = new ColorModelImpl();

	// Default
	this->pos = vec3();
	this->rot = quat();
	this->scale = vec3(1, 1, 1);
}

ColorModel::~ColorModel()
{
	// Implement
	delete impl;
}

void ColorModel::loadVAO(vector<vec3> vertices, vector<vec2> colors, vector<unsigned int> indices)
{
	impl->VAO.init();
	impl->VAO.bind();
	impl->VAO.addAttribute(vertices);
	impl->VAO.addAttribute(colors);
	// impl->VAO.addAttribute(normals);
	impl->VAO.addIndices(indices);
	impl->VAO.unbind();
}

void ColorModel::render(vec3 _pos, quat _rot, vec3 _scale)
{
	
	#ifdef LOG
	LOG
	#endif

	// Frustumcull
	// if (!Graphic::ins.camera.frustumCulling.sphere(position, 0));
	// 	return;
	// if (!Graphic::ins.camera.frustumCulling.point(position));
	// 	return;

	// Shader
	this->shader.use();

	#ifdef LOG
	LOG
	#endif

	// Model mattrix
	vec3 finalPos = this->pos + _pos;
	quat finalRot = _rot ^ this->rot;
	vec3 finalScale = vec3(this->scale.x * _scale.x, this->scale.z * _scale.z, this->scale.z * _scale.z);
	mat4 matModel;
	matModel.translate(finalPos);
	matModel.rotate(finalRot);
	matModel.scale(finalScale);
	this->shader.setMat4(2, matModel);

	#ifdef LOG
	LOG
	#endif

	// VAO
	impl->VAO.bind();
	// VAO.renderTriangle();
	impl->VAO.drawElementTriangle();
	impl->VAO.unbind();
	
	#ifdef LOG
	LOG
	#endif

}

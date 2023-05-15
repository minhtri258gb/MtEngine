#define __MT_SIMPLE_MODEL_CPP__

#include "common.h"
#include "../Graphic.h"
#include "SimpleModel.h"

using namespace mt::graphic;

ShaderProgram SimpleModel::shader;

SimpleModel::SimpleModel()
{
}

SimpleModel::~SimpleModel()
{
}

void SimpleModel::render()
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
	matModel.translate(position); // matModel = glm::translate(matModel, this->position);
	matModel.rotate(angle); // matModel *= glm::mat4_cast(this->angle);
	matModel.scale(scale); // matModel = glm::scale(matModel, this->scale);
	shader.setMat4(2, matModel);

	// Texture
	this->texture.bind();

	// VAO
	this->VAO.bind();
	// VAO.renderTriangle();
	this->VAO.drawElementTriangle();
	this->VAO.unbind();
}

#define __MT_SIMPLE_MODEL_CPP__

#include "common.h"
#include "../Graphic.h"
#include "../buffer/VertexArrayObject.h"
#include "../texture/Texture.h"
#include "SimpleModel.h"

using namespace std;
using namespace mt::graphic;

ShaderProgram SimpleModel::shader;


class SimpleModel::SimpleModelImpl
{
public:
	VertexArrayObject VAO;
	Texture texture;
};

SimpleModel::SimpleModel()
{
	// Implement
	impl = new SimpleModelImpl();
}

SimpleModel::~SimpleModel()
{
	// Implement
	delete impl;
}

void SimpleModel::loadVAO(vector<vec3> vertices, vector<vec2> texcoords, vector<vec3> normals, vector<unsigned int> indices)
{
	impl->VAO.init();
	impl->VAO.bind();
	impl->VAO.addAttribute(vertices);
	impl->VAO.addAttribute(texcoords);
	impl->VAO.addAttribute(normals);
	impl->VAO.addIndices(indices);
	impl->VAO.unbind();
}

void SimpleModel::loadVAO(vector<vec3> vertices, vector<vec2> texcoords, vector<unsigned int> indices)
{
	impl->VAO.init();
	impl->VAO.bind();
	impl->VAO.addAttribute(vertices);
	impl->VAO.addAttribute(texcoords);
	impl->VAO.addIndices(indices);
	impl->VAO.unbind();
}

void SimpleModel::loadVAO(vector<vec3> vertices, vector<unsigned int> indices)
{
	impl->VAO.init();
	impl->VAO.bind();
	impl->VAO.addAttribute(vertices);
	impl->VAO.addIndices(indices);
	impl->VAO.unbind();
}

void SimpleModel::loadTexture(string filepath)
{
	impl->texture.init(filepath);
}

void SimpleModel::render()
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
	matModel.translate(this->pos); // matModel = glm::translate(matModel, this->position);
	matModel.rotate(this->rot); // matModel *= glm::mat4_cast(this->angle);
	matModel.scale(this->scale); // matModel = glm::scale(matModel, this->scale);
	this->shader.setMat4(2, matModel);

	// Texture
	impl->texture.bind();

	// VAO
	impl->VAO.bind();
	// VAO.renderTriangle();
	impl->VAO.drawElementTriangle();
	impl->VAO.unbind();
}

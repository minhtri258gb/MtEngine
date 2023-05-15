#define __MT_MODEL_BUILDER_CPP__

#include "common.h"
#include "../Graphic.h"
#include "ModelBuilder.h"
#include "SimpleModel.h"

using namespace std;
using namespace mt::graphic;

class ModelBuilder::ModelBuilderImpl
{
public:
	
};

ModelBuilder::ModelBuilder()
{
	// Implement
	this->impl = new ModelBuilderImpl();
}

ModelBuilder::~ModelBuilder()
{
	// Implement
	delete this->impl;
}

Model* ModelBuilder::loadModel(std::string name)
{
	Model* model = this->createDefaultModel(name);
	if (!model)
	{
		// Create memory
		SimpleModel *newModel = new SimpleModel();

		// Read config #TODO

		// Read data #TODO
		vector<vec3> vertices;
		vertices.push_back(vec3( 0.5f,  0.5f, 0.0f));
		vertices.push_back(vec3( 0.5f, -0.5f, 0.0f));
		vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
		vertices.push_back(vec3(-0.5f,  0.5f, 0.0f));
		
		vector<vec2> texcoords;
		texcoords.push_back(vec2(1.0f, 1.0f));
		texcoords.push_back(vec2(1.0f, 0.0f));
		texcoords.push_back(vec2(0.0f, 0.0f));
		texcoords.push_back(vec2(0.0f, 1.0f));
		
		vector<unsigned int> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(3);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);

		// Load data to VAO
		newModel->VAO.init();
		// VAO.setCount(vertices.size());
		newModel->VAO.bind();
		newModel->VAO.addAttribute(vertices);
		newModel->VAO.addAttribute(texcoords);
		newModel->VAO.addIndices(indices);
		newModel->VAO.unbind();

		// Load Material
		newModel->texture.init("../res/textures/wall.jpg");

		// Override class
		model = newModel;
	}
	return model;
}

Model* ModelBuilder::createDefaultModel(string _name)
{
	if (_name == "box")
		return this->createBox();
	else if (_name == "plane")
		return this->createPlane();
	
	return nullptr;
}

Model* ModelBuilder::createBox()
{
	SimpleModel *model = new SimpleModel();

	vector<vec3> vertices;
	vertices.push_back(vec3( 2.0f,  2.0f,  2.0f));
	vertices.push_back(vec3( 2.0f,  2.0f, -2.0f));
	vertices.push_back(vec3( 2.0f, -2.0f,  2.0f));
	vertices.push_back(vec3( 2.0f, -2.0f, -2.0f));
	vertices.push_back(vec3(-2.0f,  2.0f,  2.0f));
	vertices.push_back(vec3(-2.0f,  2.0f, -2.0f));
	vertices.push_back(vec3(-2.0f, -2.0f,  2.0f));
	vertices.push_back(vec3(-2.0f, -2.0f, -2.0f));
	
	// vector<vec2> texcoords;
	// texcoords.push_back(vec2(1.0f, 1.0f));
	// texcoords.push_back(vec2(1.0f, 0.0f));
	// texcoords.push_back(vec2(1.0f, 1.0f));
	// texcoords.push_back(vec2(1.0f, 0.0f));
	
	// texcoords.push_back(vec2(0.0f, 1.0f));
	// texcoords.push_back(vec2(0.0f, 0.0f));
	// texcoords.push_back(vec2(0.0f, 1.0f));
	// texcoords.push_back(vec2(0.0f, 0.0f));

	vector<unsigned int> indices;
	indices.push_back(0); indices.push_back(1); indices.push_back(3);
	indices.push_back(0); indices.push_back(3); indices.push_back(2);
	indices.push_back(6); indices.push_back(7); indices.push_back(5);
	indices.push_back(6); indices.push_back(5); indices.push_back(4);
	indices.push_back(2); indices.push_back(3); indices.push_back(7);
	indices.push_back(2); indices.push_back(7); indices.push_back(6);
	indices.push_back(4); indices.push_back(5); indices.push_back(1);
	indices.push_back(4); indices.push_back(1); indices.push_back(0);
	indices.push_back(6); indices.push_back(4); indices.push_back(0);
	indices.push_back(6); indices.push_back(0); indices.push_back(2);
	indices.push_back(5); indices.push_back(7); indices.push_back(3);
	indices.push_back(5); indices.push_back(3); indices.push_back(1);
	
	model->VAO.init();
	model->VAO.bind();
	model->VAO.addAttribute(vertices);
	// model->VAO.addAttribute(texcoords);
	model->VAO.addIndices(indices);
	model->VAO.unbind();

	// model->texture.init("../res/textures/default.png");

	return model;
}

Model* ModelBuilder::createPlane()
{
	SimpleModel *model = new SimpleModel();

	vector<vec3> vertices;
	vertices.push_back(vec3(-0.5f, 0.0f, -0.5f));
	vertices.push_back(vec3( 0.5f, 0.0f, -0.5f));
	vertices.push_back(vec3(-0.5f, 0.0f,  0.5f));
	vertices.push_back(vec3( 0.5f, 0.0f,  0.5f));

	vector<vec2> texcoords;
	texcoords.push_back(vec2(0.0f, 1.0f));
	texcoords.push_back(vec2(1.0f, 1.0f));
	texcoords.push_back(vec2(0.0f, 0.0f));
	texcoords.push_back(vec2(1.0f, 0.0f));

	vector<unsigned int> indices;
	indices.push_back(0); indices.push_back(2); indices.push_back(1);
	indices.push_back(1); indices.push_back(2); indices.push_back(3);
	
	model->VAO.init();
	model->VAO.bind();
	model->VAO.addAttribute(vertices);
	model->VAO.addAttribute(texcoords);
	model->VAO.addIndices(indices);
	model->VAO.unbind();

	model->texture.init("../res/textures/default.tga");

	return model;
}

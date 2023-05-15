#define __MT_SKYBOX_CPP__

#include "common.h"
#include "../Graphic.h"
#include "SkyBox.h"
#include "../buffer/VertexArrayObject.h"
#include "../texture/TextureCube.h"

using namespace std;
using namespace mt;
using namespace mt::graphic;

class SkyBox::SkyBoxImpl {
public:
	VertexArrayObject VAO;
	TextureCube texture;
	vec3 fogColour;
};

ShaderProgram SkyBox::shader;

SkyBox::SkyBox()
{
	// Implement
	impl = new SkyBoxImpl();

	// Default
	sun = nullptr;
}

SkyBox::~SkyBox()
{
	// Implement
	delete impl;

	// Component
	if (sun)
		delete sun;
}

void SkyBox::init(string name)
{
	// Data
	// CFGFile fCFG("res/skybox/" + name + "/info.cfg");

	// Mesh sky
	float size = 1024.0f;
	vector<vec3> vertices;
	vertices.push_back(vec3( size,  size,  size));
	vertices.push_back(vec3( size,  size, -size));
	vertices.push_back(vec3( size, -size,  size));
	vertices.push_back(vec3( size, -size, -size));
	vertices.push_back(vec3(-size,  size,  size));
	vertices.push_back(vec3(-size,  size, -size));
	vertices.push_back(vec3(-size, -size,  size));
	vertices.push_back(vec3(-size, -size, -size));

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

	impl->VAO.init();
	impl->VAO.bind();
	impl->VAO.addAttribute(vertices);
	impl->VAO.addIndices(indices);
	impl->VAO.unbind();

	// Texture sky
	impl->texture.init("../res/textures/sky/ely_hills/hills_X.tga");

	// // Sun
	// fCFG.select("[sun]");
	// vec3 sunOrigin = fCFG.getVec3("origin");
	// if(sunOrigin.length() != 0.0)
	// 	sun = new Sun(sunOrigin);

	// // Fog
	// fCFG.select("[fog]");
	// fogColour = fCFG.getVec3("colour");
	// fogColour *= (1.0f / 255.0f);

	// // Shader
	// m_idProgram = g_pGraphic->loadShader("res/shader/skybox_vertex.glsl", "res/shader/skybox_fragment.glsl");
	// g_pGraphic->use(m_idProgram);

	// g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgram, "ourTexture"), 0);
	// g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgram, "projection"), g_pGraphic->getProjectionMat());
	// // g_pGraphic->setUniform(g_pGraphic->getLocation(m_idProgram, "fogColour"), getFogColour());

	// m_viewLoc = g_pGraphic->getLocation(m_idProgram, "view");
}

void SkyBox::render()
{
	shader.use();

	impl->texture.bind();

	Graphic::ins.setDepthTest(false);

	impl->VAO.bind();
	impl->VAO.drawElementTriangle();
	impl->VAO.unbind();

	Graphic::ins.setDepthTest(true);
}

// vec3 SkyBox::getSunDirect()
// {
// 	// if(sun)
// 	// 	return sun->light->getDirect();
// 	// else
// 	// 	return vec3();
// }

// vec3 SkyBox::getSunOrigin()
// {
// 	// if(sun)
// 	// 	return sun->getOrigin();
// 	// else
// 	// 	return vec3();
// }

// vec3 SkyBox::getFogColour()
// {
// 	// return fogColour;
// }

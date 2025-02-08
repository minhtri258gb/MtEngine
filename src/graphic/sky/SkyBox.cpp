#define __MT_SKYBOX_CPP__

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "SkyBox.h"

#include "engine/file/FileCFG.h"
#include "graphic/buffer/VertexArrayObject.h"
#include "graphic/texture/TextureCube.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


class SkyBox::SkyBoxImpl {
public:
	VertexArrayObject VAO;
	TextureCube texture;
	vec3 fogColour;
};

ShaderProgram SkyBox::shader;


SkyBox::SkyBox() {
	LOG("SkyBox");
	try {

		// Implement
		impl = new SkyBoxImpl();

		// Default
		sun = nullptr;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
SkyBox::~SkyBox() {
	LOG("~SkyBox");

	// Implement
	delete impl;

	// Component
	if (sun)
		delete sun;
}

void SkyBox::init(std::string textureName) {
	LOG("init");
	try {

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
		impl->texture.init(Config::ins.skybox_path + textureName + "/X.tga");

		// // Sun
		// fCFG.select("[sun]");
		// vec3 sunOrigin = fCFG.getVec3("origin");
		// if (sunOrigin.length() != 0.0)
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
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void SkyBox::render() {
	LOG("render");
	try {

		shader.use();

		impl->texture.bind();

		Graphic::ins.setDepthTest(false);

		impl->VAO.bind();
		impl->VAO.drawElementTriangle();
		impl->VAO.unbind();

		Graphic::ins.setDepthTest(true);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void SkyBox::clear() {
	LOG("clear");
	try {
		// Ko có con trỏ cần giải phóng
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

// vec3 SkyBox::getSunDirect()
// {
// 	// if (sun)
// 	// 	return sun->light->getDirect();
// 	// else
// 	// 	return vec3();
// }

// vec3 SkyBox::getSunOrigin()
// {
// 	// if (sun)
// 	// 	return sun->getOrigin();
// 	// else
// 	// 	return vec3();
// }

// vec3 SkyBox::getFogColour()
// {
// 	// return fogColour;
// }

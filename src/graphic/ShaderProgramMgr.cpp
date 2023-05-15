#define __MT_SHADER_PROGRAM_NAMAGER_CPP__

#include "common.h"
#include "ShaderProgramMgr.h"
#include "models/SimpleModel.h"
#include "models/animation/AnimationModel.h"
#include "particles/Sprite.h"
#include "sky/SkyBox.h"
#include "terrain/StaticTerrain.h"
// #include "terrain/Terrain.h"
#include "hud/Text.h"

using namespace std;
using namespace mt;
using namespace mt::graphic;

ShaderProgramMgr::ShaderProgramMgr()
{
}

ShaderProgramMgr::~ShaderProgramMgr()
{
}

void ShaderProgramMgr::init()
{
	// Simple Model
	SimpleModel::shader.init("simple",	ShaderProgram::SHADER_TYPE::VERTEX |
										ShaderProgram::SHADER_TYPE::FRAGMENT);
	SimpleModel::shader.use();
	SimpleModel::shader.addLocation("proj");		// 0
	SimpleModel::shader.addLocation("view");		// 1
	SimpleModel::shader.addLocation("model");		// 2
	SimpleModel::shader.addLocation("ourTexture");	// 3
	SimpleModel::shader.setInt(3, 0);

	// Animation Model
	AnimationModel::shader.init("skinning",	ShaderProgram::SHADER_TYPE::VERTEX |
											ShaderProgram::SHADER_TYPE::FRAGMENT);
	AnimationModel::shader.use();
	AnimationModel::shader.addLocation("proj");			// 0
	AnimationModel::shader.addLocation("view");			// 1
	AnimationModel::shader.addLocation("model");		// 2
	AnimationModel::shader.addLocation("bones");		// 3
	AnimationModel::shader.addLocation("diff_texture");	// 4
	AnimationModel::shader.setInt(4, 0);
	
	// Sprite
	Sprite::shader.init("particles",	ShaderProgram::SHADER_TYPE::VERTEX |
										ShaderProgram::SHADER_TYPE::FRAGMENT |
										ShaderProgram::SHADER_TYPE::GEOMETRY);
	Sprite::shader.use();
	Sprite::shader.addLocation("proj");			// 0
	Sprite::shader.addLocation("view");			// 1
	Sprite::shader.addLocation("cameraPos");	// 2
	Sprite::shader.addLocation("ourTexture");	// 3
	Sprite::shader.setInt(3, 0);

	// SkyBox
	SkyBox::shader.init("skybox",	ShaderProgram::SHADER_TYPE::VERTEX |
									ShaderProgram::SHADER_TYPE::FRAGMENT);
	SkyBox::shader.use();
	SkyBox::shader.addLocation("proj");			// 0
	SkyBox::shader.addLocation("view");			// 1

	// Static Terrain
	StaticTerrain::shader.init("terrain_static",	ShaderProgram::SHADER_TYPE::VERTEX |
													ShaderProgram::SHADER_TYPE::FRAGMENT);
	StaticTerrain::shader.use();
	StaticTerrain::shader.addLocation("proj");			// 0
	StaticTerrain::shader.addLocation("view");			// 1

	// // Terrain
	// Terrain::shader.init("terrain",	ShaderProgram::SHADER_TYPE::VERTEX |
	// 								ShaderProgram::SHADER_TYPE::FRAGMENT |
	// 								ShaderProgram::SHADER_TYPE::TESS_CONTROL |
	// 								ShaderProgram::SHADER_TYPE::TESS_EVALUATION);
	// // Terrain::shader.init("terrain_static",	ShaderProgram::SHADER_TYPE::VERTEX |
	// // 										ShaderProgram::SHADER_TYPE::FRAGMENT);
	// Terrain::shader.use();
	// Terrain::shader.addLocation("proj");			// 0
	// Terrain::shader.addLocation("view");			// 1
	// Terrain::shader.addLocation("ourTexture");		// 2
	// Terrain::shader.addLocation("heightMapTex");	// 3
	// Terrain::shader.setInt(2, 0);
	// Terrain::shader.setInt(3, 1);

	// Text
	Text::shader.use();
	Text::shader.addLocation("proj");		// 0
	Text::shader.addLocation("ourTexture");	// 1
	Text::shader.addLocation("color");		// 2

	// #EXTRA
}

void ShaderProgramMgr::close()
{
	// Simple Model
	SimpleModel::shader.close();
	
	// Animation Model
	AnimationModel::shader.close();

	// Sprite
	Sprite::shader.close();

	// SkyBox
	SkyBox::shader.close();

	// Static Terrain
	StaticTerrain::shader.close();

	// Terrain
	// Terrain::shader.close();

	// Text
	Text::shader.close();

	// #EXTRA
}

void ShaderProgramMgr::setSceneProj(mat4 value)
{
	SimpleModel::shader.use();
	SimpleModel::shader.setMat4(0, value);
	AnimationModel::shader.use();
	AnimationModel::shader.setMat4(0, value);
	Sprite::shader.use();
	Sprite::shader.setMat4(0, value);
	SkyBox::shader.use();
	SkyBox::shader.setMat4(0, value);
	StaticTerrain::shader.use();
	StaticTerrain::shader.setMat4(0, value);
	// Terrain::shader.use();
	// Terrain::shader.setMat4(0, value);
}

void ShaderProgramMgr::setSceneView(mat4 value)
{
	SimpleModel::shader.use();
	SimpleModel::shader.setMat4(1, value);
	AnimationModel::shader.use();
	AnimationModel::shader.setMat4(1, value);
	Sprite::shader.use();
	Sprite::shader.setMat4(1, value);
	// sky
	mat4 viewTmp = value;
	viewTmp[12] = viewTmp[13] = viewTmp[14] = 0.0f;
	SkyBox::shader.use();
	SkyBox::shader.setMat4(1, viewTmp);
	StaticTerrain::shader.use();
	StaticTerrain::shader.setMat4(1, value);
	// Terrain::shader.use();
	// Terrain::shader.setMat4(1, value);
}

void ShaderProgramMgr::setScreenProj(mat4 value)
{
	Text::shader.setMat4(0, value);
}

void ShaderProgramMgr::setScreenView(mat4 value)
{

}

void ShaderProgramMgr::setCameraPosition(vec3 value)
{
	Sprite::shader.use();
	Sprite::shader.setVec3(2, value);
}

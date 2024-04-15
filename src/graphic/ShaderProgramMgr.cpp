#define __MT_SHADER_PROGRAM_NAMAGER_CPP__

#include <list>

#include "common.h"
#include "ShaderProgramMgr.h"
#include "models/SimpleModel.h"
#include "models/ColorModel.h"
#include "models/animation/AnimationModel.h"
#include "sky/SkyBox.h"
#include "terrain/StaticTerrain.h"
#include "terrain/Terrain.h"
#include "bsp/BspSourceMap.h"
#include "bsp/BspQuakeMap.h"
#include "bsp/BspMap.h"
#include "particles/Sprite.h"
#include "particles/Emitter.h"
#include "hud/Text.h"
#include "other/DebugFrame.h"

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
	SimpleModel::shader.init("mdlSimple",	ShaderProgram::SHADER_TYPE::VERTEX |
											ShaderProgram::SHADER_TYPE::FRAGMENT);
	SimpleModel::shader.use();
	SimpleModel::shader.addLocation("proj");		// 0
	SimpleModel::shader.addLocation("view");		// 1
	SimpleModel::shader.addLocation("model");		// 2
	SimpleModel::shader.addLocation("ourTexture");	// 3
	SimpleModel::shader.addLocation("camPos");		// 4
	SimpleModel::shader.setInt(3, 0);

	// Color Model
	ColorModel::shader.init("mdlColor",	ShaderProgram::SHADER_TYPE::VERTEX |
										ShaderProgram::SHADER_TYPE::FRAGMENT);
	ColorModel::shader.use();
	ColorModel::shader.addLocation("proj");		// 0
	ColorModel::shader.addLocation("view");		// 1
	ColorModel::shader.addLocation("model");		// 2
	ColorModel::shader.addLocation("camPos");		// 3

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
	StaticTerrain::shader.addLocation("ourTexture");	// 2
	StaticTerrain::shader.setInt(2, 0);

	// Terrain QuaTree
	Terrain::shader.init("terrain",	ShaderProgram::SHADER_TYPE::VERTEX |
									ShaderProgram::SHADER_TYPE::FRAGMENT |
									ShaderProgram::SHADER_TYPE::TESS_CONTROL |
									ShaderProgram::SHADER_TYPE::TESS_EVALUATION);
	Terrain::shader.use();
	Terrain::shader.addLocation("proj");			// 0
	Terrain::shader.addLocation("view");			// 1
	Terrain::shader.addLocation("texColor");		// 2
	Terrain::shader.addLocation("texHeight");		// 3
	Terrain::shader.addLocation("heightScale");		// 4
	Terrain::shader.setInt(2, 0);
	Terrain::shader.setInt(3, 1);

	// BspSourceMap
	BspSourceMap::shader.init("bsp_source",	ShaderProgram::SHADER_TYPE::VERTEX |
											ShaderProgram::SHADER_TYPE::FRAGMENT);
	BspSourceMap::shader.use();
	BspSourceMap::shader.addLocation("proj");	// 0
	BspSourceMap::shader.addLocation("view");	// 1
	BspSourceMap::shader.addLocation("model");	// 2

	// BspQuakeMap
	BspQuakeMap::shader.init("bsp_quake",	ShaderProgram::SHADER_TYPE::VERTEX |
											ShaderProgram::SHADER_TYPE::FRAGMENT);
	BspQuakeMap::shader.use();
	BspQuakeMap::shader.addLocation("proj");		// 0
	BspQuakeMap::shader.addLocation("view");		// 1
	BspQuakeMap::shader.addLocation("model");		// 2
	BspQuakeMap::shader.addLocation("ourTexture");	// 3
	BspQuakeMap::shader.setInt(3, 0);

	// BspMap
	BspMap::shader.init("bsp",	ShaderProgram::SHADER_TYPE::VERTEX |
								ShaderProgram::SHADER_TYPE::FRAGMENT);
	BspMap::shader.use();
	BspMap::shader.addLocation("proj");			// 0
	BspMap::shader.addLocation("view");			// 1
	BspMap::shader.addLocation("model");		// 2
	BspMap::shader.addLocation("ourTexture");	// 3
	BspMap::shader.setInt(3, 0);

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

	// Emitter
	Emitter::shader.init("emitter",	ShaderProgram::SHADER_TYPE::VERTEX |
									ShaderProgram::SHADER_TYPE::FRAGMENT |
									ShaderProgram::SHADER_TYPE::GEOMETRY);
	Emitter::shader.use();
	Emitter::shader.addLocation("proj");		// 0
	Emitter::shader.addLocation("view");		// 1
	Emitter::shader.addLocation("cameraPos");	// 2
	Emitter::shader.addLocation("colrowNum");	// 3
	Emitter::shader.addLocation("ourTexture");	// 4
	Emitter::shader.setInt(4, 0);

	// Text
	Text::shader.init("text",	ShaderProgram::SHADER_TYPE::VERTEX |
								ShaderProgram::SHADER_TYPE::FRAGMENT);
	Text::shader.use();
	Text::shader.addLocation("proj");		// 0
	Text::shader.addLocation("ourTexture");	// 1
	Text::shader.addLocation("textColor");	// 2


	// // DebugFrame
	// DebugFrame::shader.init("debug",	ShaderProgram::SHADER_TYPE::VERTEX |
	// 									ShaderProgram::SHADER_TYPE::FRAGMENT);
	// DebugFrame::shader.use();
	// DebugFrame::shader.addLocation("proj");		// 0
	// DebugFrame::shader.addLocation("view");		// 1
	// DebugFrame::shader.addLocation("model");	// 2

	// #EXTRA
}

void ShaderProgramMgr::close()
{
	// Enviroment
	SkyBox::shader.close();
	StaticTerrain::shader.close();
	Terrain::shader.close();
	BspSourceMap::shader.close();
	BspQuakeMap::shader.close();
	BspMap::shader.close();

	// Model
	SimpleModel::shader.close();
	ColorModel::shader.close();
	AnimationModel::shader.close();

	// Sprite
	Sprite::shader.close();

	// Emitter
	Emitter::shader.close();

	// Text
	Text::shader.close();

	// Other
	// DebugFrame::shader.close();

	// #EXTRA
}

void ShaderProgramMgr::setSceneProj(mat4 value)
{
	SimpleModel::shader.use();
	SimpleModel::shader.setMat4(0, value);
	ColorModel::shader.use();
	ColorModel::shader.setMat4(0, value);
	AnimationModel::shader.use();
	AnimationModel::shader.setMat4(0, value);
	Sprite::shader.use();
	Sprite::shader.setMat4(0, value);
	Emitter::shader.use();
	Emitter::shader.setMat4(0, value);
	SkyBox::shader.use();
	SkyBox::shader.setMat4(0, value);
	StaticTerrain::shader.use();
	StaticTerrain::shader.setMat4(0, value);
	Terrain::shader.use();
	Terrain::shader.setMat4(0, value);
	BspSourceMap::shader.use();
	BspSourceMap::shader.setMat4(0, value);
	BspQuakeMap::shader.use();
	BspQuakeMap::shader.setMat4(0, value);
	BspMap::shader.use();
	BspMap::shader.setMat4(0, value);
	// Text::shader.use();
	// Text::shader.setMat4(0, value);
	// DebugFrame::shader.use();
	// DebugFrame::shader.setMat4(0, value);
}

void ShaderProgramMgr::setSceneView(mat4 value)
{
	SimpleModel::shader.use();
	SimpleModel::shader.setMat4(1, value);
	ColorModel::shader.use();
	ColorModel::shader.setMat4(1, value);
	AnimationModel::shader.use();
	AnimationModel::shader.setMat4(1, value);
	Sprite::shader.use();
	Sprite::shader.setMat4(1, value);
	Emitter::shader.use();
	Emitter::shader.setMat4(1, value);
	// sky
	mat4 viewTmp = value;
	viewTmp[12] = viewTmp[13] = viewTmp[14] = 0.0f;
	SkyBox::shader.use();
	SkyBox::shader.setMat4(1, viewTmp);
	StaticTerrain::shader.use();
	StaticTerrain::shader.setMat4(1, value);
	Terrain::shader.use();
	Terrain::shader.setMat4(1, value);
	BspSourceMap::shader.use();
	BspSourceMap::shader.setMat4(1, value);
	BspQuakeMap::shader.use();
	BspQuakeMap::shader.setMat4(1, value);
	BspMap::shader.use();
	BspMap::shader.setMat4(1, value);
	// Text::shader.use();
	// Text::shader.setMat4(1, value);
	// DebugFrame::shader.use();
	// DebugFrame::shader.setMat4(1, value);
}

void ShaderProgramMgr::setScreenProj(mat4 value)
{
	Text::shader.use();
	Text::shader.setMat4(0, value);
}

void ShaderProgramMgr::setScreenView(mat4 value)
{

}

void ShaderProgramMgr::setCameraPosition(vec3 value)
{
	SimpleModel::shader.use();
	SimpleModel::shader.setVec3(4, value);
	ColorModel::shader.use();
	ColorModel::shader.setVec3(3, value);

	Sprite::shader.use();
	Sprite::shader.setVec3(2, value);
	
	Emitter::shader.use();
	Emitter::shader.setVec3(2, value);
}

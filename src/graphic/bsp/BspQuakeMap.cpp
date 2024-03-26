#define __MT_BSP_QUAKE_MAP_CPP__

#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"
#include "engine/math/Math.h"
#include "graphic/Graphic.h"
#include "BspQuakeMap.h"

#include "graphic/buffer/VertexArrayObject.h"
#include "graphic/texture/Texture.h"

#include "./bsp4/Math.hpp"
#include "./bsp4/Q3BspRenderHelpers.hpp"
#include "./bsp4/Q3Bsp.hpp"
#include "./bsp4/Q3BspMap.hpp"

#include "./bsp4/Q3BspLoader.hpp"
#include "./bsp4/StringHelpers.hpp"

using namespace std;
using namespace mt;
using namespace mt::graphic;

ShaderProgram BspQuakeMap::shader;


bool FindEntityAttribute(const std::string &entity, const char *entityName, const char *attribName, std::string &output)
{
    output.clear();
    std::string trimmedEntity = StringHelpers::trim(entity, '\n');
    std::string attribValueFinal("");
    std::string attribValueRead("");
    bool attribFound = false;

    auto tokens = StringHelpers::tokenizeString(trimmedEntity.c_str(), '\n');

    for (auto &t : tokens)
    {
        auto attribs = StringHelpers::tokenizeString(t.c_str(), ' ', 2);

        for (auto &a : attribs)
        {
            a = StringHelpers::trim(a, '"');
        }

        if (!strncmp(attribs[0].c_str(), attribName, strlen(attribs[0].c_str())))
        {
            attribValueRead = attribs[1];
        }

        if (!strncmp(attribs[1].c_str(), entityName, strlen(attribs[1].c_str())))
        {   
            attribFound = true;
        }
    }

    if (attribFound)
        output = attribValueRead;

    return attribFound;
}
vec3 FindPlayerStart(const char *entities)
{
    std::string str(entities);
    vec3 result(0.0f, 0.0f, 4.0f); // some arbitrary position in case there's no info_player_deathmatch on map
    size_t pos = 0;

    std::string playerStartCoords("");

    while (pos != std::string::npos)
    {
        size_t posOpen = str.find("{", pos);
        size_t posClose = str.find("}", posOpen);

        if (posOpen != std::string::npos)
        {
            std::string entity = str.substr(posOpen + 1, posClose - posOpen - 1);
            if (FindEntityAttribute(entity, "info_player_deathmatch", "origin", playerStartCoords))
                break;
        }

        pos = posClose;
    }

    if (!playerStartCoords.empty())
    {
        auto coords = StringHelpers::tokenizeString(playerStartCoords.c_str(), ' ');

        result.x = std::stof(coords[0]);
        result.y = std::stof(coords[1]);
        result.z = std::stof(coords[2]);
    }

    return result;
}

class BspQuakeMap::BspQuakeMapImpl
{
public:
	VertexArrayObject VAO;
	
	Q3BspMap* m_q3map;
};

BspQuakeMap::BspQuakeMap()
{
	// Component
	// impl->map = new bsp("./res/bsp/de_dust2.bsp");
	// impl->map = new bsp("./res/bsp/css_cs_deadhouse_1.0/cs_deadhouse.bsp");
	// impl->map = new bsp("./res/bsp/source/CS_Sklad_Top-X/maps/cs_sklad_top-x.bsp");

	// Implement
	impl = new BspQuakeMapImpl();
}

BspQuakeMap::~BspQuakeMap()
{
	// Component
	// delete impl->map;

	// Implement
	delete impl;
}

void BspQuakeMap::init(string name)
{
	Q3BspLoader loader;
	// impl->m_q3map = loader.Load("./res/quake/1++/1++.bsp");
	// impl->m_q3map = loader.Load("./res/quake/1smallmap/1smallmap.bsp");
	// impl->m_q3map = loader.Load("./res/quake/ntkjidm2.bsp");
	// impl->m_q3map = loader.Load("./res/quake/agorafobia/maps/agorafobia.bsp"); // crash map
	// impl->m_q3map = loader.Load("./res/quake/maps/air2.bsp"); // lag
	// impl->m_q3map = loader.Load("./res/quake/maps/test_bigbox.bsp"); // box
	// impl->m_q3map = loader.Load("./res/quake/maps/texturegrab.bsp"); // nhieu texture
	// impl->m_q3map = loader.Load("aggressor"); // oke
	impl->m_q3map = loader.Load("test1"); // oke

	vec3 startPos;
	if (impl->m_q3map)
	{
			impl->m_q3map->Init();
			impl->m_q3map->ToggleRenderFlag(Q3RenderUseLightmaps);

			// try to locate the first info_player_deathmatch entity and place the camera there
			startPos = FindPlayerStart(static_cast<Q3BspMap *>(impl->m_q3map)->entities.ents);

			// Graphic::ins.camera.position = startPos;
	} else {
		cout << "[ERR] Khong load duoc map" << endl;
	}
}

void BspQuakeMap::update()
{
	impl->m_q3map->CalculateVisibleFaces(Graphic::ins.camera.position);
}

void BspQuakeMap::render()
{

	this->shader.use();

	// Model Mat
	mat4 modelMat;
	modelMat.rotate(quat(Math::toRadian(-90.0), vec3 (1,0,0)));
	// modelMat.scale(1.0f);
	// Tham khao: glUniform1f(ShaderManager::GetInstance()->UseShaderProgram(ShaderManager::BasicShader).uniforms[WorldScaleFactor], );
	modelMat.scale(1.f / Q3BspMap::s_worldScale);
	this->shader.setMat4(2, modelMat);
	
	// // Graphic::ins.wireframe(true);
	// Graphic::ins.cullFaceToogle(false);

	// // impl->texture.bind();

	impl->m_q3map->OnRenderStart();
	impl->m_q3map->Render();
	impl->m_q3map->OnRenderFinish();
	
	// impl->VAO.bind();
	// impl->VAO.drawElementTriangle();
	// impl->VAO.unbind();

	// // Graphic::ins.wireframe(false);
	// Graphic::ins.cullFaceToogle(true);
}

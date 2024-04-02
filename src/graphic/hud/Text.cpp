#define __MT_TEXT_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include <freetype/freetype.h>

#include "common.h"
#include "engine/Config.h"
#include "../Graphic.h"
#include "Text.h"

#include "../buffer/VertexArrayObject.h"

// #include "../../Main.h"
// #include "../../system/System.h"
// #include "../../graphic/Graphic.h"
// #include "../../graphic/Window.h"
// #include "../../graphic/Scene.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;

struct Character
{
	unsigned int TextureID;		// ID handle of the glyph texture
	vec2i Size;					// Size of glyph
	vec2i Bearing;				// Offset from baseline to left/top of glyph
	unsigned int Advance;		// Offset to advance to next glyph
};

bool isInit = false;
ShaderProgram Text::shader;
VertexArrayObject VAO;
map<char, Character> characters;

class Text::TextImpl
{
public:

	string content;
	vec2 position;
	float scale;
	vec3 color;

};

Text::Text()
{
	// Implement
	impl = new TextImpl();

	// Data
	impl->content = "";
	impl->position = vec2();
	impl->scale = 1.0f;
	impl->color = vec3(1,1,1);
}

Text::~Text()
{
	// Implement
	delete impl;
}

void Text::init(string content, vec2 position, float scale, vec3 color)
{
	if (!isInit)
	{
		isInit = true;

		// Vertex Buffer
		vector<unsigned int> indices;
		indices.push_back(0); indices.push_back(3); indices.push_back(1);
		indices.push_back(0); indices.push_back(2); indices.push_back(3);

		vector<vec4> vertices;
		vertices.resize(4, vec4());

		VAO.init();
		VAO.bind();
		VAO.addDynamicAttribute(4, 4);
		VAO.addIndices(indices);
		VAO.unbind();

		// Init Font
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			throw error("Could not init FreeType Library");
		
		FT_Face face;
		if (FT_New_Face(ft, "res/font/Desyrel.ttf", 0, &face))
			throw error("Failed to load font");
		
		FT_Set_Pixel_Sizes(face, 0, 48);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
		for (GLubyte c = 32; c < 128; c++)
		{
			// Load character glyph
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				throw error("Failed to load Glyph");
			
			FT_GlyphSlot g = face->glyph;

			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
					GL_TEXTURE_2D, 0,
					GL_RED, g->bitmap.width, g->bitmap.rows, 0,
					GL_RED,
					GL_UNSIGNED_BYTE, g->bitmap.buffer);

			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Now store character for later use
			Character character = {
				texture,
				vec2i(g->bitmap.width,
				g->bitmap.rows),
				vec2i(g->bitmap_left, g->bitmap_top),
				(unsigned int) g->advance.x
			};
			characters.insert(pair<GLchar,Character>(c, character));
		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}
	
	// Value
	impl->content = content;
	impl->position = position;
	impl->position.x *= (float)Config::ins.windowWidth;
	impl->position.y *= (float)Config::ins.windowHeight;
	impl->scale = scale;
	impl->color = color;
}

void Text::render()
{
	shader.use();

	Graphic::ins.setDepthTest(false);

	VAO.bind();

	glActiveTexture(GL_TEXTURE0);

	shader.setVec3(2, impl->color);

	vec2 offset = impl->position;

	for (auto c : impl->content)
	{
		Character ch = characters[c];

		if (c == 10) // new line
		{
			offset.x = impl->position.x;
			offset.y -= 50.0f * impl->scale;
			continue;
		}

		float xpos = offset.x + ch.Bearing.x * impl->scale;
		float ypos = offset.y - (ch.Size.y - ch.Bearing.y) * impl->scale;

		float w = ch.Size.x * impl->scale;
		float h = ch.Size.y * impl->scale;

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// Update VBO for each character
		vector<vec4> vertices;
		vertices.resize(4);
		vertices[0] = vec4(xpos,     ypos,     0.0, 1.0);
		vertices[1] = vec4(xpos,     ypos + h, 0.0, 0.0);
		vertices[2] = vec4(xpos + w, ypos,     1.0, 1.0);
		vertices[3] = vec4(xpos + w, ypos + h, 1.0, 0.0);

		// Update content of VBO memory
		VAO.updateDynamicAttribute(0, vertices);
		
		// Render quad
		VAO.drawElementTriangle();

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		offset.x += (ch.Advance >> 6) * impl->scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

	// POST render
	VAO.unbind();

	Graphic::ins.setDepthMark(true);
}

void Text::setContent(string content)
{
	impl->content = content;
}

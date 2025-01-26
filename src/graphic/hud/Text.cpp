#define __MT_TEXT_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include <freetype/freetype.h>

#include "common.h"
#include "engine/Config.h"
#include "graphic/Graphic.h"
#include "graphic/buffer/VertexArrayObject.h"
#include "Text.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


struct Character {
	unsigned int TextureID;		// ID handle of the glyph texture
	vec2i Size;					// Size of glyph
	vec2i Bearing;				// Offset from baseline to left/top of glyph
	unsigned int Advance;		// Offset to advance to next glyph
};

ShaderProgram Text::shader;

class Text::TextImpl {
public:

	static VertexArrayObject VAO;
	static map<char, Character> characters;

	string content;
	vec2 position;
	float scale;
	vec3 color;

};

VertexArrayObject Text::TextImpl::VAO;
map<char, Character> Text::TextImpl::characters;

void Text::initText() {
	// Vertex Buffer
	vector<vec2> texcoords;
	texcoords.push_back(vec2(0.0f, 1.0f));
	texcoords.push_back(vec2(0.0f, 0.0f));
	texcoords.push_back(vec2(1.0f, 1.0f));
	texcoords.push_back(vec2(1.0f, 0.0f));
	vector<uint> indices;
	// indices.push_back(0); indices.push_back(3); indices.push_back(1);
	// indices.push_back(0); indices.push_back(2); indices.push_back(3);
	indices.push_back(0); indices.push_back(2); indices.push_back(1);
	indices.push_back(1); indices.push_back(2); indices.push_back(3);
	Text::TextImpl::VAO.init();
	Text::TextImpl::VAO.bind();
	Text::TextImpl::VAO.addAttribute(texcoords);
	Text::TextImpl::VAO.addDynamicAttribute(4, vec2());
	Text::TextImpl::VAO.addIndices(indices);
	Text::TextImpl::VAO.unbind();

	// Init Font
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		throw error("FREETYPE_INIT_FAIL", "Could not init FreeType Library");

	FT_Face face;
	if (FT_New_Face(ft, (Config::ins.font_path + "desyrel.ttf").c_str(), 0, &face)) // #TODO move config
		throw error("FONT_LOAD_FAIL", "Failed to load font");

	FT_Set_Pixel_Sizes(face, 0, 48);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
	for (GLubyte c = 32; c < 128; c++) {
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			throw error("GLYPH_LOAD_FAIL", "Failed to load Glyph");
		
		FT_GlyphSlot g = face->glyph;

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D, 0,
			GL_RED, g->bitmap.width, g->bitmap.rows, 0,
			GL_RED,
			GL_UNSIGNED_BYTE, g->bitmap.buffer
		);

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
		Text::TextImpl::characters.insert(pair<GLchar,Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

Text::Text() {
	// Implement
	impl = new TextImpl();

	// Data
	impl->content = "";
	impl->position = vec2();
	impl->scale = 1.0f;
	impl->color = vec3(1, 1, 1);
}

Text::~Text() {
	// Implement
	delete impl;
}

void Text::init(string _content, vec2 _position, float _scale, vec3 _color) {
	impl->content = _content;
	impl->position = _position;
	impl->position.x *= (float)Config::ins.windowWidth;
	impl->position.y *= (float)Config::ins.windowHeight;
	impl->scale = _scale;
	impl->color = _color;
}

void Text::render() {
	this->shader.use();

	Graphic::ins.cullFaceToogle(false);
	Graphic::ins.setDepthTest(false);

	Text::TextImpl::VAO.bind();

	glActiveTexture(GL_TEXTURE0);

	this->shader.setVec3(2, impl->color);

	vec2 offset = impl->position;

	for (auto c : impl->content) {
		Character ch = Text::TextImpl::characters[c];

		if (c == 10) { // new line
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
		vector<vec2> vertices;
		// vertices.resize(4);
		// vertices[0] = vec4(xpos,     ypos,     0.0, 1.0);
		// vertices[1] = vec4(xpos,     ypos + h, 0.0, 0.0);
		// vertices[2] = vec4(xpos + w, ypos,     1.0, 1.0);
		// vertices[3] = vec4(xpos + w, ypos + h, 1.0, 0.0);
	
		vertices.push_back(vec2( 50.0f, -50.0f));
		vertices.push_back(vec2(-500.0f, -500.0f));
		vertices.push_back(vec2( 500.0f, -500.0f));
		vertices.push_back(vec2(-500.0f,  500.0f));
		// vertices.push_back(vec2( 500.0f,  500.0f));

		// Update content of VBO memory
		Text::TextImpl::VAO.updateDynamicAttribute(1, vertices);

		// Render quad
		Text::TextImpl::VAO.drawElementTriangle();

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		offset.x += (ch.Advance >> 6) * impl->scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

	// POST render
	Text::TextImpl::VAO.unbind();

	Graphic::ins.setDepthMark(true);
	Graphic::ins.cullFaceToogle(true);
}

void Text::setContent(string content) {
	impl->content = content;
}

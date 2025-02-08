#define __MT_FONT_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include <freetype/freetype.h>

#include "common.h"
#include "Font.h"

using namespace std;
using namespace mt;
using namespace mt::graphic;

class Font::FontImpl {
public:

	// Datatype
	struct Character {
		unsigned int TextureID;		// ID handle of the glyph texture
		vec2i Size;					// Size of glyph
		vec2i Bearing;				// Offset from baseline to left/top of glyph
		unsigned int Advance;		// Offset to advance to next glyph
	};

	// Variables
	map<char, Character> Characters;
};

ShaderProgram Font::shader;

Font::Font() {
	// Implement
	impl = new FontImpl;
}

Font::~Font() {
	// Implement
	delete impl;
}

void Font::init() {
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		throw error("FREETYPE_INIT_FAIL", "Could not init FreeType Library");

	FT_Face face;
	if (FT_New_Face(ft, "./res/fonts/OCRAEXT.ttf", 0, &face))
		throw error("FONT_LOAD_FAIL", "Failed to load font");

	FT_Set_Pixel_Sizes(face, 0, 48);

	// Load per char
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

	for (unsigned char c=0; c<128; c++) {
		// load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			throw error("GLYPH_LOAD_FAIL", "Failed to load Glyph");

		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		FontImpl::Character character = {
			texture,
			vec2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			vec2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(unsigned int)face->glyph->advance.x
		};
		impl->Characters.insert(pair<char, FontImpl::Character>(c, character));
	}
}

void Font::render() {

}

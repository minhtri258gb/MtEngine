#define __MT_TEXTURE_ATLAS_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include "common.h"
#include "TextureAtlas.h"

using namespace std;
using namespace mt::graphic;

TextureAtlas::TextureAtlas()
{
	gl_textureId = -1;
	column = row = 1;
}

TextureAtlas::~TextureAtlas()
{
	glDeleteTextures(1, &gl_textureId);
}

void TextureAtlas::init(string filepath, int column, int row)
{
    // Data
    this->column = column;
    this->row = row;
    
    // OpenGL
	glGenTextures(1, &gl_textureId);
    glBindTexture(GL_TEXTURE_2D, gl_textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
		glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    	throw warning("[TextureAtlas::load] Failed to load texture: " + filepath);

    stbi_image_free(data);
}

void TextureAtlas::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gl_textureId);
}

int TextureAtlas::getColumn()
{
	return this->column;
}

int TextureAtlas::getRow()
{
	return this->row;
}

void TextureAtlas::getCoordOffset(int index, float &u, float &v)
{
	u = (index % this->column) * 1.0f / this->column;
	v = (index / this->row) * 1.0f / this->row;
}

void TextureAtlas::getSizeTile(float &u, float &v)
{
	u = 1.0f / this->column;
	v = 1.0f / this->row;
}

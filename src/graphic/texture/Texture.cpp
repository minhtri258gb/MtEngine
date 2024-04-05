#define __MT_TEXTURE_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include "common.h"
#include "Texture.h"

using namespace std;
using namespace mt::graphic;

Texture::Texture()
{
	gl_textureId = -1;
}

Texture::~Texture()
{
	glDeleteTextures(1, &gl_textureId);
}

void Texture::init(string filepath, bool _flip)
{
	glGenTextures(1, &gl_textureId);
	glBindTexture(GL_TEXTURE_2D, gl_textureId);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 3);

	// flip
	stbi_set_flip_vertically_on_load(_flip);

	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
		throw error("Failed to load texture: " + filepath);
	
	if (nrChannels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else if (nrChannels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else if (nrChannels == 1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	
	stbi_image_free(data);
}

void Texture::bind(unsigned int location)
{
	glActiveTexture(GL_TEXTURE0 + location);
	glBindTexture(GL_TEXTURE_2D, gl_textureId);
}

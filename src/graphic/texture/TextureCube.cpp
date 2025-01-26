#define __MT_TEXTURE_CUBE_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include "common.h"
#include "TextureCube.h"

using namespace std;
using namespace mt::graphic;


TextureCube::TextureCube() {
	gl_textureId = -1;
}

TextureCube::~TextureCube() {
	glDeleteTextures(6, &gl_textureId);
}

/*
 * EX: filepath = "./res/name-X.png"
 */
void TextureCube::init(string filepath, bool _flip) {
	// tao 6 link file
	vector<string> textures;
	textures.resize(6);

	int pos = filepath.find_last_of('.') - 1;

	string lstChar = "RLUDBF"; // RLUDBF // RLUDFB
	for (int i=0; i<6; i++) {
		filepath[pos] = lstChar[i];
		textures[i] = filepath;
	}

	// opengl
	glGenTextures(1, &gl_textureId);
		glBindTexture(GL_TEXTURE_CUBE_MAP, gl_textureId);

	// flip
	stbi_set_flip_vertically_on_load(_flip);

	// load and generate the texture
	int width, height, nrChannels;
	for (int i = 0; i < 6; i++) {
		unsigned char *data = stbi_load(textures[i].c_str(), &width, &height, &nrChannels, 0);
		if (!data)
			throw error("LOAD_FAIL", "Failed to load texture: " + textures.at(i));
		
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void TextureCube::bind(unsigned int location) {
	glActiveTexture(GL_TEXTURE0 + location);
	glBindTexture(GL_TEXTURE_CUBE_MAP, gl_textureId);
}

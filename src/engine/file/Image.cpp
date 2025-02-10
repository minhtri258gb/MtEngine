#define __MT_IMAGE_CPP__

#include <stb_image.h>

#include "common.h"
#include "engine/Log.h"
#include "Image.h"

using namespace std;
using namespace mt;
using namespace mt::engine;


Image::Image() {
	LOG("Image");
	try {
		flip = false;
		data = nullptr;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

Image::~Image() {
	LOG("~Image");

	if (data)
		stbi_image_free(data);
}

unsigned char Image::at(unsigned int index) const {
	return data[index * nrChannels];
}
void Image::load(string filepath) {
	LOG("load");
	try {
		stbi_set_flip_vertically_on_load(flip);

		data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

		if (!data)
			throw error("LOAD_FAIL", "Failed to load texture: " + filepath);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

int Image::getWidth() {
	return width;
}
int Image::getHeight() {
	return height;
}
int Image::getChannel() {
	return nrChannels;
}
unsigned char* Image::getDataPtr() {
	return data;
}

unsigned char Image::operator [] (unsigned int index) const {
	return data[index * nrChannels];
}

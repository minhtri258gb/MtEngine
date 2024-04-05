#define __MT_IMAGE_CPP__

#include <stb_image.h>

#include "common.h"
#include "Image.h"

using namespace std;
using namespace mt;

Image::Image()
{
	flip = false;
	data = nullptr;
}

Image::~Image()
{
	if (data)
		stbi_image_free(data);
}

void Image::load(string filepath)
{
	stbi_set_flip_vertically_on_load(flip);

	data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

	if (!data)
		throw error("Failed to load texture: " + filepath);
}

int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}

int Image::getChannel()
{
	return nrChannels;
}

unsigned char* Image::getDataPtr()
{
	return data;
}

unsigned char Image::operator [] (unsigned int index) const
{
	return data[index * nrChannels];
}
